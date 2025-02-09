﻿#pragma once
#include <windows.h>
#include <time.h>

#define left 75
#define right 77
#define up 72
#define down 80
#define space 32
#define attack 82
#define item 113

#define maxBullet 10
#define initialReloadSpeed 300
#define doubleSpeed 115
#define gBoardWidth 40
#define gBoardHeight 20
#define gBoardOx 0
#define gBoardOy 0

//gameboard 2차원 배열
char gameBoardInfo[][23][42];
char currentGameBoard[23][42];

//모델
char bulletModel[2][1];
char bossEnemyModel[4][4];

char enemyModel[1][1];
char kingAnimalModel[][2][4];
char animalModel[1][2];

//enum color
/*0.검정색 1.파란색 2.초록색
	3.옥색	 4.빨간색 5.자주색
	6.노란색 7.흰색   8.회색
	9.연파랑 10.연초록 11.연한옥색
	12.연빨강 13.연자주 14.연노랑 15. 진한흰색*/
typedef enum color{
	green = 2,		//나무
	red = 4,		//enemy, 설치불가능바리케이드
	purple =5,		//animal
	white = 7,		//기본 색깔
	gray = 8,		//바위
	lightBlue = 9,	//pc
	lightYellow = 11//설치가능바리케이드
}enumColor;

//UI
int enemyNumber;
int bulletNumber;
int itemNumber;

//커서
int curPosX, curPosY;

//Position
typedef struct _Position {
	int X;
	int Y;
} posStruct;

//PC

typedef struct _PC {
	posStruct pos;
	int speed;
	int reloadSpeed;
	int itemCode;
} pc;

typedef struct bossNPC {
	posStruct pos;
	int speed;
	int hp;
	boolean activeStatus;
} bossStruct;

//NPC - enemy
typedef struct _EnemyNPC {
	posStruct pos;
	int speed;
	int id;
	int hp;
	int type;
	int dodgeDirection;
	int dodgeCount;
    int direction;
	posStruct deadPos;
	clock_t deadTime;
	boolean activeStatus;
	boolean dieFlag;
	struct _EnemyNPC *next;
} enemyNPC;

//NPC - enemylist
typedef struct _EnemyNPCList {
	int enemyCurrentNumber;
	enemyNPC *enemyHeader;
} enemyNPCList;

//NPC - animal
typedef struct _AnimalNPC {
	posStruct pos;
	int speed;
	int direction;
	boolean activeStatus;
}animalNPC;


//one-player 전역변수
pc playableCharacter;

//test용 NPC 전역변수
animalNPC animalArray[3];
enemyNPCList *enemyList;


//함수 선언부
posStruct getPCCurrentPos();
void setPCCurrentPos(int moveX, int moveY);
posStruct getEnemyCurrentPos(int enemyId);
void setEnemyCurrentPos(int enemyId, int moveX, int moveY);
posStruct getAnimalCurrentPos(animalNPC * animal);
void setAnimalCurrentPos(animalNPC * animal, int moveX, int moveY);
void setPcReloadSpeed(int reloadSpeed);
void setCurrentGameBoard(int stage);

void removeCursor();
void changeConsoleColor(enumColor consoleColor);
void restoreConsoleColor();
void setCurrentCursorPos(int posX, int posY);
COORD getCurrentCursorPos(void);