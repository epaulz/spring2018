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
#include <netdb.h>

int main(int argc, char *argv[]){
	int sk;
	struct sockaddr_in skaddr;
	struct hostent *hp;
	
	if(argc != 4){
		printf("Usage: ./client <server name> <server port> <input file>\n");
		exit(0);
	}
	
	// create a socket
	if((sk = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		printf("Problem creating socket\n");
		exit(1);
	}
	
	// specify server address and port number we want to connect to
	skaddr.sin_family = AF_INET;
	
	// convert argv[1] to a network byte order binary IP adress
	// first, try to convert using gethostbyname
	if((hp = gethostbyname(argv[1])) != 0){
		// name lookup was successful - copy the IP address
		memcpy(&skaddr.sin_addr.s_addr, hp->h_addr, hp->h_length);
	}
	else{
		// name lookup was unsuccessful - try converting from dotted decimal
		#ifndef SUN
			if(inet_aton(argv[1], &skaddr.sin_addr) == 0){
				printf("Invalid IP address: %s\n", argv[1]);
				exit(1);
			}
		#else
			// inet_aton is missing on Solaris - use inet_addr
			skaddr.sin_addr.s_addr = inet_addr(argv[1]);
			if(skaddr.sin_addr.s_addr == -1){
				printf("Invalid IP address: %s\n", argv[1]);
				exit(1);
			}
		#endif
	}
	
	skaddr.sin_port = htons(atoi(argv[2]));
	
	// attempt to establish a connection with the server
	if(connect(sk, (struct sockaddr*)&skaddr, sizeof(skaddr)) < 0){
		printf("Problem connecting socket\n");
		exit(1);
	}
	
	// send a string and finish
	FILE* inFile = fopen(argv[3], "r");
	char line[256];
	
	while(fgets(line, sizeof(line), inFile)){
		write(sk, line, strlen(line));
	}
	
	fclose(inFile);
	close(sk);
	return 0;
}