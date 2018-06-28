/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	HW #2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	int ld, sd, addrlen, length, n;
	char buff[100];
	struct sockaddr_in skaddr;
	struct sockaddr_in from;
	
	// check for proper usage
	if(argc != 2){
		printf("Usage: ./server <port>\n");
		exit(0);
	}
	
	// create a socket
	if((ld = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("Problem creating socket\n");
		exit(1);
	}
	
	// establish our address and port number (from command line)
	skaddr.sin_family = AF_INET;
	skaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	skaddr.sin_port = htons(atoi(argv[1]));
	
	if(bind(ld, (struct sockaddr*)&skaddr, sizeof(skaddr)) < 0){
		perror("Problem binding\n");
		exit(0);
	}
	
	length = sizeof(skaddr);
	if(getsockname(ld, (struct sockaddr*)&skaddr, &length) < 0){
		perror("Error getsockname\n");
		exit(1);
	}
	
	printf("The Server passive socket port number is %d\n", ntohs(skaddr.sin_port));
	
	// put the socket into passive mode (waiting for connections)
	if(listen(ld, 5) < 0){
		perror("Error calling listen\n");
		exit(1);
	}
	
	// process incoming connections until program is stopped
	while(1){
		printf("Ready for a connection...\n");
		
		addrlen = sizeof(skaddr);
		if((sd = accept(ld, (struct sockaddr*)&from, &addrlen)) < 0){
			perror("Problem with accept call\n");
			exit(1);
		}
		
		printf("Got a connection - processing...\n");
		
		// determine and print out the address of the new server socket
		length = sizeof(skaddr);
		if(getsockname(sd, (struct sockaddr*)&skaddr, &length) < 0){
			perror("Error getsockname\n");
			exit(1);
		}
		
		printf("\nThe active server port number is %d\n", ntohs(skaddr.sin_port));
		printf("The active server IP address is %s\n\n", inet_ntoa(skaddr.sin_addr));
		
		//print out the address of the client
		printf("The client port number is %d\n", ntohs(from.sin_port));
		printf("The client IP address is %s\n\n", inet_ntoa(from.sin_addr));
		
		// read and send to stdout until the client closes the connection
		printf("Message from client:\n");
		while((n = read(sd, buff, 100)) > 0){
			write(1, buff, n);
		}
		
		printf("\nDone with connection - closing\n\n\n");
		close(sd);
		exit(1);
	}
}