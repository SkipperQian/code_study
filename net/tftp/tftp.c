#include "tftp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <errno.h>

int servIsRunning;

int Tftp_SendAck(int sock, unsigned short block)
{
	ssize_t sentBytes;
	TFTP_HDR ack;

	ack.cmd = htons(TFTP_ACK);
	ack.block = htons(block);
	sentBytes = send(sock, &ack, TFTP_ACK_SIZE, 0);
	if (sentBytes <= 0)
	{
		printf("[%s] send ack failed\n", __func__);
		return -1;
	}

	return 0;
}

int Tftp_DataIsValid(TFTP_HDR *hdr, unsigned short curBlock)
{
	if (hdr->cmd == TFTP_DATA && hdr->block == curBlock)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Tftp_RecvData(int sock, FILE *fp)
{
	int ret;
	unsigned int waitUs = 0;
	ssize_t recvBytes;
	TFTP_HDR *hdr;
	unsigned short expectBlock = 1;

	hdr = (TFTP_HDR *)malloc(TFTP_HDR_SIZE + DATA_SIZE_MAX);
	if (hdr == NULL)
	{
		return -1;
	}

	do
	{
		for (waitUs = 0; waitUs < WAIT_TIME_US_MAX; waitUs += 20000)
		{
			recvBytes = recv(sock, hdr, TFTP_HDR_SIZE + DATA_SIZE_MAX, MSG_DONTWAIT);
			if (recvBytes <= TFTP_HDR_SIZE)
			{
				/*printf("[%s] recv failed\n", __func__);*/
			}
			else
			{
				hdr->cmd = ntohs(hdr->cmd);
				hdr->block = ntohs(hdr->block);
				if (Tftp_DataIsValid(hdr, expectBlock))
				{
					fwrite(hdr->data, 1, recvBytes - TFTP_HDR_SIZE, fp);
				}
				break;
			}
			usleep(20000);
		}
		if (waitUs >= WAIT_TIME_US_MAX)
		{
			free(hdr);
			return -1;
		}

		ret = Tftp_SendAck(sock, hdr->block);
		if (ret != 0)
		{
			free(hdr);
			return -1;
		}

		expectBlock++;
	} while (recvBytes == (TFTP_HDR_SIZE + DATA_SIZE_MAX));

	free(hdr);
	return 0;
}

int Tftp_HandleWrq(int sock, TFTP_REQ *req)
{
	char fullFileName[256] = {0};
	char path[] = "./";
	TFTP_HDR *hdr = &req->msg;
	FILE *fp;
	int ret;

	sprintf(fullFileName, "%s", path);
	strncpy(fullFileName + strlen(path), TFTP_FILENAME(hdr), 256 - strlen(path));
	printf("[%s] file: %s\n", __func__, fullFileName);

	fp = fopen(fullFileName, "w");
	if (fp == NULL)
	{
		printf("[%s] fopen failed\n", __func__);
		return -1;
	}

	ret = Tftp_SendAck(sock, BLOCK_WRQ_ACK);
	if (ret != 0)
	{
		fclose(fp);
		return -1;
	}

	Tftp_RecvData(sock, fp);

	fclose(fp);

	return 0;
}

void *Tftp_HandleTsk(void *arg)
{
	TFTP_REQ *req = (TFTP_REQ *)arg;
	int sd;
	int ret;
	struct sockaddr_in saddr;
	socklen_t clen = sizeof(struct sockaddr_in);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1)
	{
		printf("[%s] serv create handle sock failed\n", __func__);
		free(req);
		return NULL;
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(0);

	ret = bind(sd, (struct sockaddr *)&saddr, sizeof(saddr));
	if (ret < 0)
	{
		printf("[%s] handle task bind failed, ret=%d %s\n", __func__, ret, strerror(errno));
		close(sd);
		free(req);
		return NULL;
	}

	ret = connect(sd, (struct sockaddr*)&(req->clientAddr), clen);
	if (ret < 0)
	{
		printf("[%s] connect clinet failed, ret=%d\n", __func__, ret);
		close(sd);
		free(req);
		return NULL;
	}

	switch (req->msg.cmd)
	{
	case TFTP_RRQ:
		/* code */
		break;
	case TFTP_WRQ:
		Tftp_HandleWrq(sd, req);
		break;
	default:
		break;
	}

	close(sd);
	free(req);
	return NULL;
}

int Tftp_CreateServ(void)
{
	int servFd;
	pthread_t tid;
	int ret;
	struct sockaddr_in saddr;
	socklen_t clen;
	TFTP_REQ *req;
	ssize_t recv_bytes;

	servFd = socket(AF_INET, SOCK_DGRAM, 0);
	if (servFd == -1)
	{
		printf("[%s] create tftp server failed\n", __func__);
		return -1;
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(TFTP_PORT);

	ret = bind(servFd, (struct sockaddr *)&saddr, sizeof(saddr));
	if (ret < 0)
	{
		printf("[%s] server bind failed with %d", __func__, ret);
		close(servFd);
		return -1;
	}

	servIsRunning = 1;
	clen = sizeof(struct sockaddr_in);

	while (servIsRunning)
	{
		req = (TFTP_REQ *)malloc(sizeof(TFTP_REQ) + REQUEST_SIZE_MAX);
		if (req == NULL)
		{
			printf("[%s] no memory\n", __func__);
			continue;
		}
		memset(req, 0, sizeof(TFTP_REQ) + REQUEST_SIZE_MAX);

		recv_bytes = recvfrom(servFd, &req->msg, REQUEST_SIZE_MAX, 0,
					(struct sockaddr *) &(req->clientAddr), &clen);
		if (recv_bytes <= 0)
		{
			free(req);
			continue;
		}

		printf("[%s] start recv\n", __func__);

		req->msg.cmd = ntohs(req->msg.cmd);
		ret = pthread_create(&tid, NULL, Tftp_HandleTsk, req);
		if (ret != 0)
		{
			printf("[%s] create thread failed, ret=%d\n", __func__, ret);
			free(req);
			continue;
		}
		req = NULL;
	}

	printf("exit TFTP server\n");

	return 0;
}
