#ifndef _FUNCS_H_
#define _FUNCS_H_

/*#include "video-graphics.h"
#include "utypes.h"
#include "kbc.h"
#include "queue.h"
#include "music.h"*/
#include "sprite.h"
#include "queue.h"
#include "music.h"
#include "pixmap.h"

// Modo 1280x1024
extern int modo_vis;

Queue keys_queue;

void programa(void);
int scancode;

extern Note alarm;

// Coluna onde sera jogada a peca
int col;

typedef struct{
	int nlin;
	int ncol;
	int cells[6][6]; 
} Board;

typedef struct{
	int num;
	Bool actual;
	int pont; 
} Player;

__dpmi_meminfo map;

void displayMenu();

Board createBoard(int lin, int col);

void displayBoard(Board tab, char *testc);

void startGame();

void play(Board tab, char *testc);

void beep();

void moveArrow(Sprite *seta, Board tab, char* base);

#endif
