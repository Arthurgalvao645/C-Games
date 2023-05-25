#include <stdio.h>
#include <time.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <windows.h> 
#include <conio.h> 
#define V 21
#define H 75
#define N 100

#define V 21
#define H 75
#define N 100



typedef struct{
	int x, y; // posi��o inicial
	int movX, movY;
	char imagen;

} snake;

typedef struct{

	int x, y;

} fruit;

snake snk[N]; // tamanho m�ximo
fruit frt;

void begin(int *size, char map[V][H]);
void intro(char map[V][H]);
void intro_data(char map[V][H], int *size);
void loop(char map[V][H], int size);
void input(char map[V][H], int *size, int *dead);
void update(char map[V][H], int size);
void intro_data2(char map[V][H], int size);
void gotoxy(int x, int y); // Esta fun��o foi sugerida por um amigo para obter melhor desempenho
void show(char map[V][H]);

int main(){
	int size;
	char map[V][H];
	begin(&size, map);
	show(map);
	system("pause");
	loop(map, size);
	system("pause");
	return 0;
}

// Inicializado em uma posi��o inicial
void begin(int *size, char map[V][H]){
	int i;
	// cabe�a de cobra
	snk[0].x = 32;
	snk[0].y = 10; // V
	// corpo de cobra
	*size = 4;
	srand(time(NULL));
	frt.x = rand() % (H - 2) + 1; // posi��o autom�tica de frutas
	frt.y = rand() % (V - 2) + 1;
	for (i = 0; i < *size; i++){

		snk[i].movX = 1;
		snk[i].movY = 0;

	} // cobra s� se move em X

	intro(map);
	intro_data(map, size);
}

// Mostrar tudo
void show(char map[V][H]){
	int i, j;
	for (i = 0; i < V; i++){

		for (j = 0; j < H; j++){

			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

// O campo (mapa).
void intro(char map[V][H]){
	int i, j;
	for (i = 0; i < V; i++){
		for (j = 0; j < H; j++){
			if (i == 0 || i == V - 1){

				map[i][j] = '-';
			}
			else if (j == 0 || j == H - 1){

				map[i][j] = '|';
			}
			else{
				map[i][j] = ' ';
			}
		}
	}
}

// Apresente cada data inIT
void intro_data(char map[V][H], int *size){
	int i;
	for (i = 1; i < *size; i++){
		snk[i].x = snk[i - 1].x - 1;
		snk[i].y = snk[i - 1].y;

		snk[i].imagen = 'X'; // Corpo
	}
	snk[0].imagen = 'O'; // Cabe�a

	// Introduza a cobra em nosso acampamento
	for (i = 0; i < *size; i++){

		map[snk[i].y][snk[i].x] = snk[i].imagen;
	}

	map[frt.y][frt.x] = 'M'; // Fruta
}

void loop(char map[V][H], int size){

	int dead;
	dead = 0;

	do{
		gotoxy(0, 0);

		show(map);
		input(map, &size, &dead);
		update(map, size); // Autom�tico

	} while (dead == 0);
}

void input(char map[V][H], int *size, int *dead){
	int i;
	char key;

	// Apenas duas maneiras de morrer, colis�o com mapa ou corpo, cada parte da cobra � uma estrutura diferente

	// VERIFIQUE AS CONDI��ES DO JOGO

	if (snk[0].x == 0 || snk[0].x == H - 1 || snk[0].y == 0 || snk[0].y == V - 1){ // 0 � a cabe�a da cobra, s� vamos avaliar quando a cabe�a colidir.

		*dead = 1;
	}

	for (i = 1; i < *size && *dead == 0; i++){

		if (snk[0].x == snk[i].x && snk[0].y == snk[i].y)
		{
			*dead = 1;
		}
	}

	// VERIFIQUE A FRUTA, SE A CABE�A SE APROXIMAR, COMA!

	if (snk[0].x == frt.x && snk[0].y == frt.y){

		*size += 1;

		snk[*size - 1].imagen = 'X';

		// Posi��o da fruta regenerada em uma posi��o aleat�ria

		frt.x = rand() % (H - 2) + 1;
		frt.y = rand() % (V - 2) + 1;
	}

	// SE MORRER � ZERO PODEMOS CONTINUAR
	if (*dead == 0){
		if (kbhit() == 1){
			key = getch();

			if (key == 's' && snk[0].movY != -1){
				snk[0].movX = 0;
				snk[0].movY = 1;
			}

			if (key == 'w' && snk[0].movY != 1){
				snk[0].movX = 0;
				snk[0].movY = -1;
			}

			if (key == 'a' && snk[0].movX != 1){
				snk[0].movX = -1;
				snk[0].movY = 0;
			}

			if (key == 'd' && snk[0].movX != -1){
				snk[0].movX = 1;
				snk[0].movY = 0;
			}
		}
	}
}

void update(char map[V][H], int size){
	// Toda vez que esta fun��o � chamada, o mapa est� sobrescrevendo
	intro(map);
	intro_data2(map, size);
}

void intro_data2(char map[V][H], int size){
	int i;
	// Corpo seguindo a cabe�a
	for (i = size - 1; i > 0; i--){ // 0 � a cabe�a. ent�o vamos diminuindo at� as extremidades
		snk[i].x = snk[i - 1].x;
		snk[i].y = snk[i - 1].y;
	}
	snk[0].x += snk[0].movX; // mais movimentos
	snk[0].y += snk[0].movY;

	// agora introduza os valores no acampamento
	for (i = 0; i < size; i++)
	{

		map[snk[i].y][snk[i].x] = snk[i].imagen;
	}
	map[frt.y][frt.x] = 'M';
}

void gotoxy(int x, int y){ // eu n�o sei que diabos � essa fun��o, originalmente eu usei outra, mas isso funciona bem (sorte) :)
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
