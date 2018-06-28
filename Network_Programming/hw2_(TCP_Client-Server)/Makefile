# Makefile for simple tcp client and server

# on solaris we need to explicitly include the socket and name server
# libraries, this because sockets are not supported by the O.S. directly,
# but are a library that calls the native (XTI) network API. 
# Leave this commented out unless you are on a Sun running Solaris

LIBS= -lsocket -lnsl

# on solaris we also need to avoid inet_aton, this flag will take care of it
CFLAG= -DSUN


# This rule describes how to build a .o file from a .c file
# -Wall tells gcc to print all warnings!

.c.o:	gcc -c -Wall ${CFLAG} $<

all: tcpserver tcpclient

server: tcpserver.o
	gcc -o tcpserver tcpserver.o

client: tcpclient.o
	gcc -o tcpclient tcpclient.o
	
clean:
	rm *.o tcpserver tcpclient
