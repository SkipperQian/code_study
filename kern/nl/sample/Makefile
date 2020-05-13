CC = gcc
CFLAGS = -Wall -g -O2

SAMPLE = nl_echo genl_echo

all:$(SAMPLE)

nl_echo:
	$(CC) $(CFLAGS) nl_echo.c -o nl_echo

genl_echo:
	$(CC) $(CFLAGS) genl_echo.c -o genl_echo

.PHONY:clean
clean:
	rm -f $(SAMPLE)
