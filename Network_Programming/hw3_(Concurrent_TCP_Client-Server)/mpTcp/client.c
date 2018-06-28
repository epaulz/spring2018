/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	Homework 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char **argv){
	
	int sk, n;
	bool w=true;
	char buff[100], fileName[50], msg[50];
	struct sockaddr_in skaddr;
	struct hostent *hp;
	
	// check for usage
	if(argc != 4){
		printf("Usage: client <server name> <server port> <myfile.txt>\n");
		exit(0);
	}

	// create socket
	if((sk = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		printf("Problem creating socket.\n");
		exit(1);
	}

	// specify address structure for server we will connect to
	skaddr.sin_family = AF_INET;

	// convert argv[1] to a network byte order binary IP address
	// first try to convert using gethostbyname
	if((hp = gethostbyname(argv[1])) != 0){
		// name lookup was successful - copy the IP address
		memcpy(&skaddr.sin_addr.s_addr, hp->h_addr, hp->h_length);
	}
	else{
		// name lookup didn't work, try converting from dotted decimal
		#ifndef SUN
			if(inet_aton(argv[1], &skaddr.sin_addr) == 0){
				printf("Invalid IP address: %s\n", argv[1]);
				exit(1);
			}
		#else
			/*inet_aton is missing on Solaris - you need to use inet_addr! */
			/* inet_addr is not as nice, the return value is -1 if it fails
			(so we need to assume that is not the right address !)
			*/
			skaddr.sin_addr.s_addr = inet_addr(argv[1]);
			if(skaddr.sin_addr.s_addr == -1){
				printf("Invalid IP address: %s\n", argv[1]);
				exit(1);
			}
		#endif
	}

	skaddr.sin_port = htons(atoi(argv[2]));

	FILE* inFile = fopen(argv[3], "r");
	strcpy(fileName, argv[3]);
	if(inFile == NULL){
		printf("Error opening file.\n");
		exit(1);
	}  

	// attempt to establish a connection with the server
	if(connect(sk, (struct sockaddr*)&skaddr, sizeof(skaddr)) < 0){
		printf("Error connecting socket.\n");
		exit(1);
	}

	// send file name and wait for ack
	while(w){
		if((send(sk, fileName, strlen(fileName), 0)) == -1){
			fprintf(stderr, "Error sending message.\n");
		}
		else{
			printf("Data sent to server from file '%s'.\n", fileName);
			n = recv(sk, msg, sizeof(msg), 0);
			if(n <= 0){
				printf("Error receiving message.\n");
			}
			
			msg[n] = '\0';
			printf("Data stored in server file '%s'.\n\n", msg);
			w = false;
		}
	}
	w = true;

	// send data
	while(fgets(buff, 100, inFile)){
		send(sk, buff, strlen(buff), 0);
		if(recv(sk, buff, 100, 0) == 0){
			printf("Error sending data.\n");
		}
	}
	printf("Data transfer successful... closing connection.\n\n");

	close(sk);
	return(0);
}
