/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	Homework 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

// thread function prototype
void *connection_handler(void *);

int main( int argc, char **argv){
	int ld, sd=0, addrLen, len;
	struct sockaddr_in skaddr;
	struct sockaddr_in from;
	
	// check for usage
	if(argc != 2){
		printf("Usage: <executable> <port>\n");
		exit(0);
	}
	
	// create socket
	if((ld = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("Error creating socket.\n");
		exit(1);
	}
	
	// establish address structure
	skaddr.sin_family = AF_INET;
	skaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	skaddr.sin_port = htons(atoi(argv[1]));
	
	if(bind(ld, (struct sockaddr*)&skaddr, sizeof(skaddr)) < 0){
		perror("Error binding.\n");
		exit(0);
	}
	
	// determine port number and print
	len = sizeof(skaddr);
	if(getsockname(ld, (struct sockaddr*)&skaddr, &len) < 0){
		perror("Error getsockname.\n");
		exit(1);
	}
	printf("Passive server socket port number: %d\n", ntohs(skaddr.sin_port));
	
	// put socket into passive mode
	if(listen(ld, 5) < 0){
		perror("Error calling listen.\n");
		exit(1);
	}
	
	// process connections forever
	while(1){
		if(sd==0)
			printf("Ready for a connection...\n\n");
		
		addrLen = sizeof(skaddr);
		if((sd = accept(ld, (struct sockaddr*)&from, &addrLen)) < 0){
			perror("Problem with accept call.\n");
			exit(1);
		}
		
		printf("Got a connection - processing...\n\n");
		
		pthread_t child;
		
		// determine address/port of new server socket and print
		len = sizeof(skaddr);
		if(getsockname(sd, (struct sockaddr*)&skaddr, &len) < 0){
			perror("Error getsockname.\n");
			exit(1);
		}
		printf("Active server port number: %d\n", ntohs(skaddr.sin_port));
		printf("Active server IP: %s\n", inet_ntoa(skaddr.sin_addr));
		
		// print client address
		if(getsockname(sd, (struct sockaddr*)&from, &len) < 0){
			perror("Error getsockname.\n");
			exit(1);
		}
		printf("Client port number: %d\n", ntohs(from.sin_port));
		printf("Client IP: %s\n\n", inet_ntoa(from.sin_addr));
		
		// create thread
		pthread_create(&child, 0, connection_handler, (void*)&sd);
	}
	
	return 0;
}

// thread function to handle data transfer for connections
void *connection_handler(void *sock_desc){
	int n=-1, m, sd=0;
	bool w=true;
	char eof=(char)0x04, buff1[100], buff2[100], buff3[100], timeStr[9], *charPtr, msg[50];
	time_t current_time;
	struct tm* timeInfo;
	
	sd = *(int*)sock_desc;
	
	// read data
	while(1){
		if((m = recv(sd, msg, 50, 0)) < 0)
			perror("Error receiving message.\n");
		else if(m==0)
			printf("Connection closed.\n");

		msg[m] = '\0';
		printf("Data received from client file '%s'.\n", msg);

		charPtr = strchr(msg, '.');
		if(charPtr!=NULL)
			*charPtr = '\0';
		
		time(&current_time);
		timeInfo = localtime(&current_time);
		strftime(timeStr, sizeof(timeStr), "%H-%M-%S", timeInfo);
		strcat(msg, "(");
		strcat(msg, timeStr);
		strcat(msg, ").txt");
		
		if((send(sd, msg, strlen(msg), 0)) < 0){
			fprintf(stderr, "Error sending message.\n");
			close(sd);
		}
		printf("Data stored in file '%s'.\n\n", msg);
		
		break;
	}
	
	FILE* newFile = fopen(msg,"w");
	if(newFile == NULL){
		perror("Error opening file.\n");
		return 0;
	}
	
	while((n = read(sd, buff1, 100)) > 0){
		int i = 0, j, k = 0;
		while(i < n){
			j = 0;
			while(buff1[i] != '\n'){
				buff2[j] = buff1[i];
				i++;
				j++;
			}
			
			buff2[j] = '\n';
			while(j >= 0){
				buff3[j] = buff2[k];
				k++;
				j--;
			}
			i++;
		}
		
		fwrite(buff3, n, 1, newFile);
		write(sd, &eof, 1);
	}
	
	if(n==0)
		printf("Data transfer successful... closing connection\n\n");
	if(newFile != NULL)
		fclose(newFile);
	
	close(sd);
	sd = 0;
	
	return 0;
}
