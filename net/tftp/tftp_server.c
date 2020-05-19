#include "tftp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	Tftp_CreateServ();
	return 0;
}


#if 0
int main(int argc, char *argv[])
{
	int sd;
	int ret;
	struct sockaddr_in saddr, caddr;
	socklen_t len;
	ssize_t recv_bytes = 0, sent_bytes = 0;
	char buf[256] = {0};

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		printf("server create socket failed with %d (%s)\n",
			errno, strerror(errno));
		return -1;
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(69);

	ret = bind(sd, (struct sockaddr *)&saddr, sizeof(saddr));
	if (ret < 0) {
		printf("server bind faile with %d (%s)\n",
			errno, strerror(errno));
		return -1;
	}

	len = sizeof(caddr);
	while ((recv_bytes = recvfrom(sd, buf, 256, 0, (struct sockaddr *)&caddr, &len)) >= 0) {
		printf("server receive %ld bytes\n", recv_bytes);

		if (recv_bytes != 0) {
			printf("recv: %s\n", buf);
			sent_bytes = sendto(sd, buf, recv_bytes, 0, (struct sockaddr *)&caddr, sizeof(caddr));
			if (sent_bytes != recv_bytes) {
				printf("send %ld bytesm, %s\n", sent_bytes, strerror(errno));
			}
		}
	}


	close(sd);

	return 0;
}
#endif