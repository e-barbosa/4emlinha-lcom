#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <stdio.h>
#include <dpmi.h>
#include <go32.h>
#include <dos.h>
#include "video-graphics.h"

typedef struct{
	int nlin;
	int ncol;
	char **cells; 
} Board;

void displayMenu();

Board createBoard(int lin, int col);

void displayBoard(Board tab, char *testc);

void play(int col);

#endif
