#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int sd, ret = 0;
	struct sockaddr_in saddr;
	ssize_t sent_bytes, recv_bytes;
	char buf[256] = {0};

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		printf("clinet create socket failed with %d (%s)\n", errno, strerror(errno));
		return -1;
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = htonl(AF_INET);
	saddr.sin_port = htons(69);
	inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr);

	sent_bytes = sendto(sd, "hello world", strlen("hello world"), 0 , (struct sockaddr *)&saddr, sizeof(saddr));
	if (sent_bytes <= 0) {
		printf("clinet send data failed, %s\n", strerror(errno));
		ret = -1;
		goto exit;
	}

	recv_bytes = recvfrom(sd, buf, 256, 0, NULL, 0);
	if (recv_bytes != sent_bytes) {
		printf("clinet recv error, recv bytes:%ld\n", recv_bytes);
		ret = -1;
		goto exit;
	}

	printf("echo: %s\n", buf);

exit:
	close(sd);
	return ret;
}
