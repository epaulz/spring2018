/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	
	l5.c
	- implementation of Layer 5
*/

#include "l5.h"
#include "l4.h"
#include <stdio.h>

// sends the named value to the receiver
int l5_write(char *name, int namelen, char *value, int valuelen){
	int temp1, temp2;
	
	// call l4_write for name and value
	temp1 = l4_write(name, namelen);
	temp2 = l4_write(value, valuelen);
	
	// check for any errors
	if(temp1 == -1 || temp2 == -1)
		return -1;
	
	return 1;
}
		
	
int l5_read(char *name, int *namelenptr, char *value, int *valuelenptr){
	int temp1, temp2;
	
	// call l4_read for name and value
	temp1 = l4_read(name, *namelenptr);
	temp2 = l4_read(value, *valuelenptr);
	
	// check for any errors
	if(temp1 == -1 || temp2 == -1)
		return -1;
	
	// assign length of read messages
	*namelenptr = temp1;
	*valuelenptr = temp2;
	
	return *namelenptr + *valuelenptr;
}