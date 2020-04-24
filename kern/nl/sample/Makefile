CC = gcc
CFLAGS = -Wall -g -O2

SAMPLE = nl_echo

all:$(SAMPLE)

nl_echo:
	$(CC) $(CFLAGS) nl_echo.c -o nl_echo

.PHONY:clean
clean:
	rm -f $(SAMPLE)
