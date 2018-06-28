/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	
	l2.
	- header file for l2.c
*/

#ifndef L2_H
#define L2_H

int l2_write(char *chunk, int len);
int l2_read(char *chunk, int max);

#endif