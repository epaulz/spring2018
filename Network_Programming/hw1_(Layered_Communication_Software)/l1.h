/*
	Eric Paulz (epaulz)
	CPSC 3600-001
	
	l1.h
	- header file for l1.c
*/

#ifndef L1_H
#define L1_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// read() and write() prototypes

extern int generror;

void init_l1(void);
int l1_write(char b);
int l1_read(char *b);
double calc_score(int nerrors, int total, int points);

#endif