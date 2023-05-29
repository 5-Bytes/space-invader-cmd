#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<string.h>
#include<conio.h>
#include<time.h>

#define ROWS 9
#define COLUMNS 28

#define ARROW_RIGHT 77
#define ARROW_LEFT 75
#define SPACE 32
#define ESC 27
#define KEY_ESP 224

void drawScene(char (*scene)[COLUMNS]);
void showScene(char (*scene)[COLUMNS]);
void move(char (*scene)[COLUMNS],int c, int *positionShip);
void shoot(char (*scene)[COLUMNS], int *positionShip);

int main() {
	int score = 0,
	lives = 3;
	char gameOver='n';
	char scene[ROWS][COLUMNS];
	int positionShip=13;

	drawScene(scene);
	
	do{
		showScene(scene);
		int c = getch();
		if(c==KEY_ESP){
			c = getch();
			move(scene,c,&positionShip);
		}
		if(c==SPACE){
			shoot(scene,&positionShip);
		}
		if(c==ESC){
			gameOver='y';
		}
		system("cls");
	}while(gameOver=='n');

    return 0;
}

void drawScene(char (*scene)[COLUMNS]){
	for(int i=0; i<ROWS; i++){
		for(int j=0;j<COLUMNS;j++){
			if(j==0){
				scene[i][j] = '[';
				continue;
			}
			else if(j==COLUMNS-1){
				scene[i][j] = ']';
				continue;
			}
			else if (i==ROWS-1 && j==13) {
				scene[i][j] = '^';
			}
			else if(i==0 && j%4==0){
				scene[i][j] = '@';
			}
			else if(i==1 && j%4==2){
				scene[i][j] = '@';
			}
			else{
				scene[i][j] = ' ';
			}
		}
	}
}

void showScene(char (*scene)[COLUMNS]){
	struct timespec wait_time = {0,5000000};
	for(int i=0; i<ROWS; i++){
		for(int j=0;j<COLUMNS;j++){
			if(scene[i][j]=='|'){
				printf("%c",scene[i][j]);
				nanosleep(&wait_time,NULL);
				scene[i][j]=' ';
			}else{
				printf("%c",scene[i][j]);
			}
			
		}
		printf("\n");
	}
}

void move(char (*scene)[COLUMNS],int c, int *positionShip){
	switch(c){
			case(ARROW_LEFT):
				if((*positionShip)>1){
					scene[ROWS-1][(*positionShip)]=' ';
					--(*positionShip);
					scene[ROWS-1][(*positionShip)]='^';
				}
				break;
			case(ARROW_RIGHT):
				if((*positionShip)<COLUMNS-2){
					scene[ROWS-1][(*positionShip)]=' ';
					++(*positionShip);
					scene[ROWS-1][(*positionShip)]='^';
				}
				break;	
		}
}

void shoot(char (*scene)[COLUMNS], int *positionShip){
		int i = ROWS-2;
		while(i>= 0 && scene[i][(*positionShip)]==' ' || scene[i][(*positionShip)]=='@'){
			scene[i][(*positionShip)]='|';
			--i;
		}
}

//ERROR EN LA FILA 2 COLUMNA 6