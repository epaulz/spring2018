/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	
	l4.h
	- header file for l4.c
*/

#ifndef L4_H
#define L4_H

int l4_write(char *msg, int len);
int l4_read(char *msg, int max);

#endif