#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int sd;
	int ret;
	struct sockaddr_in saddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		printf("server create socket failed with %d (%s)\n",
			errno, strerror(errno));
		return -1;
	}

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(69);

	ret = bind(sd, (struct sockaddr *)&saddr, sizeof(saddr));
	if (ret < 0) {
		printf("server bind faile with %d (%s)\n",
			errno, strerror(errno));
		return -1;
	}


	close(sd);

	return 0;
}
