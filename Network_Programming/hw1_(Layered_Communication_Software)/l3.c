/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	
	l3.c
	- implementation of Layer 3
*/

#include "l2.h"
#include "l3.h"
#include <stdbool.h>
#include <stdio.h>

// sends a message of length 'len'.  The bytes sent are specified by 'msg'
int l3_write(char *msg, int len){
	int i, j, temp, sent = 0;
	char chunkBuf[10];
	
	// determine number of chunks in message and round up
	int chunkCount = len / 10;
	if(len % 10)
		chunkCount++;
	
	// store message in chunkBuf
	for(i = 0; (i < chunkCount) && (temp != -1); i++){
		for(j = 0; (j < 10) && ((j+sent) < len); j++){
			chunkBuf[j] = msg[j+sent];
		}
		
		// keep track of how many bytes have been read
		temp = l2_write(chunkBuf, j);
		sent += temp;
	}
	
	// check for errors
	if(temp == -1)
		return -1;
	
	// indicate end of message
	chunkBuf[0] = (char)0x03;
	l2_write(chunkBuf, 1);
	
	return sent;
}

// reads a message and stores in memory starting at the address of 'msg'.  
// no more than 'max' bytes will be put into memory, so 'max' must limit 
// the size of the message read no matter how large the message was 
// sent by 'l3_write'
int l3_read(char *msg, int max){
	int i, temp, read = 0;
	char chunkBuf[10];
	
	// read in message from chunkBuf into memory
	while(read < max){
		temp = l2_read(chunkBuf, 10);
		
		if(temp == -1)
			return -1;
		
		for(i = 0; (i < temp) && ((read+i) < max); i++){
			msg[read+i] = chunkBuf[i];
		}
		
		read += i;
		
		// check for errors
		if(i < temp)
			return -1;
		if(msg[read-1] == (char)0x03)
			return read-1;
	}
	
	if(read == max){
		if(l2_read(chunkBuf, 1) == -1)
			return -1;
		if(chunkBuf[0] == 0x00)
			return read-1;
		else
			return -1;
	}
	
	return read-1;
}	