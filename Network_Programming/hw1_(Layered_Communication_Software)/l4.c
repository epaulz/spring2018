/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	
	l4.c
	- implementation of Layer 4
*/

#include "l3.h"
#include "l4.h"
#include <stdbool.h>
#include <stdio.h>

// sends a message of length 'len'.  The bytes sent are specified by 'msg'.  
// adds a checksum to end of message to provide error checking.
int l4_write(char *msg, int len){
	int i;
	int checkCount = 0;
	
	// add up bytes in msg
	for(i = 0; i < len; i++){
		checkCount += msg[i];
	}
	
	// calculate checksum value
	char checkSum = checkCount % 256;
	
	// create a new message with checksum appended
	const int newLen = len + 1;
	char newMsg[newLen];
	for(i = 0; i < len; i++){
		newMsg[i] = msg[i];
	}
	
	newMsg[newLen-1] = newMsg[newLen-2];
	newMsg[newLen-2] = checkSum;
	
	// call l3_write with new message
	int a = l3_write(newMsg, newLen);
	
	// check for errors
	if(a == -1 || a != newLen)
		return -1;
	
	return a;
}

// reads a message into memory starting at the address specified by 'msg'.
// no more than max bytes will be put into memory, so 'max' must limit 
// the size of the message read.
int l4_read(char *msg, int max){
	int i, checkCount = 0;
	
	// read message
	int a = l3_read(msg, max);
	
	// check for errors
	if(a == -1)
		return -1;

	// add up bytes in message
	for(i = 0; i < a-2; i++){
		checkCount += msg[i];
	}
	
	// check that the checksums match
	if(msg[a-2] != checkCount % 256){
		printf("ERROR: transmission error (checksum failed)\n");
	}
	
	// remove checksum value from message
	a--;
	msg[a-1] = '\0';
	
	return a;
}