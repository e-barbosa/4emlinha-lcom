#include "funcs.h"

int modo_vis = 0x4105;
Note alarm = {C4, 150};

void kbd_isr();

Board createBoard(int lin, int col)
{
	Board tabuleiro;
	tabuleiro.nlin = lin;
	tabuleiro.ncol = col;

	
	return tabuleiro;
}

void displayMenu()
{
	int op_menu;

	printf("===================================\n");
	printf("   Bem-vindo ao Quatro em Linha!   \n");
	printf("===================================\n\n");
	
	printf("Escolha uma opcao, digitando o seu numero:\n");
	
	printf("[1] Novo Jogo\n");
	printf("[2] Sair\n");
	scanf("%d", &op_menu);
	
	startGame();
}
	
void startGame()
{	
	char *testc;
	testc = enter_graphics(modo_vis, &map);
	
	_go32_dpmi_seginfo old_kbd_irq;
	install_asm_irq_handler(KBD_IRQ, kbd_isr, &old_kbd_irq);
	
	queueInit(&keys_queue);
	
	disable_irq(KBD_IRQ);
	enable_irq(KBD_IRQ);

	Board tab = createBoard(6, 6);
	displayBoard(tab, testc);

	getchar();
	
	leave_graphics(map);
}

void displayBoard(Board tab, char *testc)
{
	char* video_base = enter_graphics(modo_vis, &map);	
	clear_screen(0, video_base);
	
	Sprite *spr1 = create_sprite(celula_azul_xpm);
	spr1->x = 0;
	spr1->y = 60;
	spr1->xspeed = 1;
	spr1->yspeed = 0;	
	draw_board(spr1, video_base, 6, 6);
	
	Sprite *spr2 = create_sprite(seta_xpm);
	spr2->x = 30;
	spr2->y = 0;
	spr2->xspeed = 1;
	spr2->yspeed = 0;	
	draw_sprite(spr2, video_base);
	
	while(queueEmpty(&keys_queue));
		
	for(;;)
	{
		moveArrow(spr2, tab, video_base);
	}
}


void moveArrow(Sprite *seta, Board tab, char* base)
{	
	int scancode;
	scancode = queueGet(&keys_queue);
	
	switch(scancode)
	{		
		case 75:{ //esquerda	
			
			Bool mexe = true;
			if(col-1<0)
			{
				mexe = false;
				col = 0;
			}
			else
				col--;
			if(mexe)
				move_sprite(seta, seta->x - 100, seta->y, base);
			scancode = 75;}
			break;
			
		case 77:{ //direita		
			
			Bool mexe = true;
			if(col+1>5)
			{
				mexe = false;
				col = 5;
			}
			else
				col++;
			
			if(mexe)
				move_sprite(seta, seta->x + 100, seta->y, base);
			
			scancode = 77;}
			break;
			
		case 76: // colocar peca
			play(tab, base);
			
			break;

		default:
			break;
	}
}



void play(Board tab, char* base)
{			
	Sprite *sprite_jog;
	
	Player jog;
	
	jog.num = 1;
	
	switch(jog.num)
	{
		case 1:
			sprite_jog = create_sprite(peca_amarela_xpm);
			break;
		case 2:
			sprite_jog = create_sprite(peca_vermelha_xpm);
			break;
	}
	
	sprite_jog->x = 7+100*col;
	
	int i;
	
	for(i = 0; i<tab.nlin; i++)
	{
		//nao esta a alterar o tabuleiro
		if(tab.cells[col][i] != 1 && tab.cells[col][i] != 2)
		{
			tab.cells[col][i] = jog.num;
			sprite_jog->y = 63+100*(tab.ncol-1-i);
			draw_sprite(sprite_jog, base);
			break;
		}
		
	}
	
	
}

void beep()
{
	play_note(&alarm);
}
