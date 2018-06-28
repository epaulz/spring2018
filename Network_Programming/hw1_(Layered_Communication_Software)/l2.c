/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	
	l2.c
	- implementation of Layer 2
*/

#include "l1.h"
#include "l2.h"
#include <stdio.h>
#include <stdbool.h>

// sends a chunk starting at the address specified by 'chunk' 
// and having length 'len'
int l2_write(char *chunk, int len){
	int i, ret = 0;
	
	if(len <= 10){
		// attempt to send message
		ret = l1_write((char)(0xFF & len));
		if(ret == -1)
			return -1;
		
		// write bytes sequentially as long as there is no error
		for(i = 0; i < len && ret != -1; i++)
			ret = l1_write(chunk[i]);
			
		if(ret != -1)
			ret = len;
		else
			ret = -1;
	}
	else{
		// message too long to be sent
		ret = -1;
	}
	
	return ret;
}

// reads a chunk and stores the incoming bytes starting at the address
// specified by 'chunk'.  No more than 'max' bytes will be put into memory,
// so 'max' limits the size of the chunk read
int l2_read(char *chunk, int max){
	int i, ret = 0;
	char len, temp;
	
	// get chunk size
	ret = l1_read(&len);
	if(ret == -1)
		return -1;
	
	// read while unread data remains AND there is no error
	for(i = 0; i < len && ret != -1; i++){
		ret = l1_read(&temp);
		
		// only write to buffer if there is room
		if(i < max)
			chunk[i] = temp;
	}
	
	return (max < len || ret == -1) ? -1 : len;
}