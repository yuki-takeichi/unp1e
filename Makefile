CC=gcc

all: tcpserv tcpcli

tcpserv: tcpserv.c netutil.c ioutil.c error.c
	$(CC) -o dist/$@ $?

tcpcli: tcpcli.c netutil.c ioutil.c error.c
	$(CC) -o dist/$@ $?

.PHONY: clean
clean:
	rm -f tcpserv
	rm -f tcpcli
	rm -f *.o
