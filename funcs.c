#include "funcs.h"

Board createBoard(int lin, int col)
{
	Board tabuleiro;
	tabuleiro.nlin = lin;
	tabuleiro.ncol = col;
	
	return tabuleiro;
}

void displayMenu()
{
	int choice;
	int mode = 0x4101;
	char *testc;
	int opcao;
	
	// Escolha da resolução do ecrã
	printf("Modo:\n");
	printf("[1] 640x480\n");
	printf("[2] 800x600\n");
	printf("[3] 1024x768\n");
	printf("[4] 1280x1024\n");
	scanf("%d", &choice);
	printf("\n");
	
	switch(choice)
	{
		case 1: 
				mode=0x4101;
				break;
		case 2: 
				mode=0x4103;
				break;
		case 3: 
				mode=0x4105;
				break;
		case 4: 
				mode=0x4107;
				break;
		default: 
			break;
	}
	
	// Ecrã de boas-vindas
	printf("Bem-vindo ao Quatro-em-Linha.\n\n");
	printf("Escolha uma opcao, digitando o seu numero:\n");
	
	printf("[1] Novo Jogo\n");
	printf("[2] Sair\n");
	
	int nlin;
	int ncol;
	
	// Escolha do tamanho do tabuleiro
	do{
			int opcao = 0;
			
			scanf("%d", &opcao);
			printf("\n");
			
			switch(opcao)
			{
				case 1:
					printf("Escolha um tamanho para o tabuleiro:\n\n");
					
					switch(mode)
					{
						case 0x4101:
							printf("[P]equeno (4x4)\n");
							break;
						
						case 0x4103:
							printf("[P]equeno (4x4)\n");
							printf("[M]edio (6x6)\n");
							break;
						
						case 0x4105:
							printf("[P]equeno (4x4)\n");
							printf("[M]edio (6x6)\n");
							printf("[G]rande (8x8)\n\n");
							break;
						
						case 0x4107:
							printf("[P]equeno (4x4)\n");
							printf("[M]edio (6x6)\n");
							printf("[G]rande (8x8)\n\n");
							break;
					}
					
					
					
					int op_tabuleiro = 0;
					
					//scanf(%d, op_tabuleiro);
					
					do{
					nlin = 0;
					printf("Linhas: ");
					scanf("%d", &nlin);
					}while(nlin < 1 || nlin > 15);
					
					do{
					ncol = 0;
					printf("Colunas: ");
					scanf("%d", &ncol);
					}while(ncol < 1 || ncol > 26);
					
					Board tab = createBoard(nlin, ncol);
	
					__dpmi_meminfo map;
	
					testc = enter_graphics(mode, &map);
		
					//displayBoard(tab, testc);
	
					if(opcao == 0)
					leave_graphics(map);
					
				case 2: exit(0);
			}
		}
		while(opcao < 1 || opcao > 2);

}

void displayBoard(int mode, char *testc)
{
/*	int opcao;
	
	int i;
	int j;
	
	draw_line(10,10,30*tab.ncol,10,1,testc);
	
	draw_line(10,10,10,30*tab.nlin,1,testc);
	
	for(i = 0; i <= tab.ncol; i++)
	{
		draw_line(10+30*i,10,10+30*i,30*tab.nlin,1,testc);
	}
	
	for(j = 0; j <= tab.nlin; j++)
	{
		draw_line(10,10+30*j,10,30*j,1,testc);
	}
	
	scanf("%d", &opcao);
	
	clear_screen(1, testc);
	
	scanf("%d", &opcao);
	*/
}
