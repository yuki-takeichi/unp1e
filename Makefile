CC=gcc

all: tcpserv tcpcli

tcpserv: tcpserv.c netutil.c ioutil.c error.c
	$(CC) -o $@ $?

tcpcli: tcpcli.c netutil.c ioutil.c error.c
	$(CC) -o $@ $?

.PHONY: clean
clean:
	rm -f tcpserv
	rm -f tcpcli
	rm -f *.o
