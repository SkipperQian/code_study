#ifndef _TFTP_H_
#define _TFTP_H_

#include <sys/socket.h>
#include <arpa/inet.h>

#define TFTP_PORT 69

#define TFTP_RRQ    1          /* read request */
#define TFTP_WRQ    2          /* write request */
#define TFTP_DATA   3          /* data packet */
#define TFTP_ACK    4          /* acknowledgement */
#define TFTP_ERROR  5          /* error code */
#define TFTP_OACK   6          /* option acknowledgement */

#define DATA_SIZE_MAX 512

#define REQUEST_SIZE_MAX 1024

#define BLOCK_WRQ_ACK 0

typedef struct _TFTP_HDR
{
	unsigned short cmd;
	union
	{
		unsigned short block;
		unsigned short code;
		char filename[2];
		char errmsg[2];
	};
	unsigned char data[0];
} TFTP_HDR;

#define TFTP_HDR_SIZE 4
#define TFTP_ACK_SIZE 4

#define TFTP_FILENAME(thdr) (thdr->filename)
#define TFTP_MODE(thdr) (thdr->filename + strlen(thdr->filename) + 1)

typedef struct _TFTP_REQ {
	unsigned int size;
	struct sockaddr_in clientAddr;
	TFTP_HDR msg;
} TFTP_REQ;

#define RETRAN_CNT_MAX 3
#define WAIT_TIME_US_MAX (3000000 * 3)


int Tftp_CreateServ(void);


#endif