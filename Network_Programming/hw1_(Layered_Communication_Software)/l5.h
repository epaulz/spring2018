/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	
	l5.h
	- header file for l5.c
*/

#ifndef L5_H
#define L5_H

int l5_write(char *name, int namelen, char *value, int valuelen);
int l5_read(char *name, int *namelenptr, char *value, int *valuelenptr);

#endif