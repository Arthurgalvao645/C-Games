#include <stdio.h>
#include <conio.h>
#include <locale.h>

char square[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

int checkwin();
void board();

int main(){
	setlocale(LC_ALL,"Portuguese");
    int player = 1, i, choice;

    char mark;
    do
    {
	board();
	player = (player % 2) ? 1 : 2;

	printf("\t\t\tJogador %d, digite um número: ", player);
	scanf("%d", &choice);

	mark = (player == 1) ? 'X' : 'O';

	if (choice == 1 && square[1] == '1')
	    square[1] = mark;

	else if (choice == 2 && square[2] == '2')
	    square[2] = mark;

	else if (choice == 3 && square[3] == '3')
	    square[3] = mark;

	else if (choice == 4 && square[4] == '4')
	    square[4] = mark;

	else if (choice == 5 && square[5] == '5')
	    square[5] = mark;

	else if (choice == 6 && square[6] == '6')
	    square[6] = mark;

	else if (choice == 7 && square[7] == '7')
	    square[7] = mark;

	else if (choice == 8 && square[8] == '8')
	    square[8] = mark;

	else if (choice == 9 && square[9] == '9')
	    square[9] = mark;

	else
	{
	    printf("\t\t\tMovimento inválido ");

	    player--;
	    getch();
	}
	i = checkwin();

	player++;
    }while (i ==  - 1);

    board();

    if (i == 1)
	printf("\t\t\t==>\aJogador %d venceu ", --player);
    else
	printf("\t\t\t==>\aFim de Jogo");

    getch();

    return 0;
}

/*********************************************
FUNÇÃO PARA RETORNAR O ESTADO DO JOGO
1 PARA JOGO ACABOU COM RESULTADO
-1 PARA O JOGO ESTÁ EM ANDAMENTO
O PARA O JOGO ACABOU SEM RESULTADO
 **********************************************/

int checkwin(){
    if (square[1] == square[2] && square[2] == square[3])
	return 1;

    else if (square[4] == square[5] && square[5] == square[6])
	return 1;

    else if (square[7] == square[8] && square[8] == square[9])
	return 1;

    else if (square[1] == square[4] && square[4] == square[7])
	return 1;

    else if (square[2] == square[5] && square[5] == square[8])
	return 1;

    else if (square[3] == square[6] && square[6] == square[9])
	return 1;

    else if (square[1] == square[5] && square[5] == square[9])
	return 1;

    else if (square[3] == square[5] && square[5] == square[7])
	return 1;

    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
	square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
	!= '7' && square[8] != '8' && square[9] != '9')

	return 0;
    else
	return  - 1;
}
/*******************************************************************
FUNÇÃO PARA DESENHAR O TABULEIRO DO JOGO DAS MARCAS COM A MARCA DOS JOGADORES
 ********************************************************************/

void board(){
    printf("\n\n\t\t\t\tJogo da velha\n\n");
    printf("\t\t\tJogador 1 (X)  -  Jogador 2 (O)\n\n\n");

    printf("\t\t\t\t     |     |     \n");
    printf("\t\t\t\t  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("\t\t\t\t_____|_____|_____\n");
    printf("\t\t\t\t     |     |     \n");

    printf("\t\t\t\t  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("\t\t\t\t_____|_____|_____\n");
    printf("\t\t\t\t     |     |     \n");

    printf("\t\t\t\t  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("\t\t\t\t     |     |     \n\n");
}
