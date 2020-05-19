CC = gcc
CFLAGS = -Wall -g -O2
CFLAGS += -I../include

SAMPLE = tftp_server tftp_client

all:$(SAMPLE)

tftp_server: tftp_server.c
	$(CC) $(CFLAGS) $< -o $@

tftp_client: tftp_client.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	rm -f $(SAMPLE)
