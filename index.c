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
void showScene(char (*scene)[COLUMNS],int score,int lives);
void move(char (*scene)[COLUMNS],int c, int *positionShip,int *turn);
void shoot(char (*scene)[COLUMNS], int positionShip, int *score);
void updatePositionInvaders(char (*scene)[COLUMNS]);

int main() {
	int score = 0,
	lives = 3;
	char gameOver='n';
	char scene[ROWS][COLUMNS];
	int positionShip=13;
	int turn = 0;

	drawScene(scene);
	
	do{
		showScene(scene, score, lives);
		int c = getch();
		if(c==KEY_ESP){
			c = getch();
			move(scene,c,&positionShip,&turn);
		}
		if(c==SPACE){
			shoot(scene,positionShip, &score);
		}
		if(c==ESC){
			gameOver='y';
		}
		if(turn == 6){
			updatePositionInvaders(scene);
			turn=0;
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

void showScene(char (*scene)[COLUMNS],int score,int lives){
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
	printf("Score: %d \t Lives:%d",score,lives);
}

void move(char (*scene)[COLUMNS],int c, int *positionShip,int *turn){
	(*turn)++;
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

void shoot(char (*scene)[COLUMNS], int positionShip, int *score){
		int i = ROWS-2;
		do{
			if(scene[i][positionShip]=='@'){
				(*score)+=10;
			}
			scene[i][positionShip]='|';
		}while(i-- > 0 && (scene[i][positionShip]==' ' || scene[i][positionShip]=='@'));
}

void updatePositionInvaders(char (*scene)[COLUMNS]){
	for (int i = ROWS-1;i>=0;i--){
		for (int j = 0; j<COLUMNS; j++){
			if(scene[i][j]=='@'){
				scene[i][j]=' ';
				scene[i+1][j]='@';
			}
		}
	}
}