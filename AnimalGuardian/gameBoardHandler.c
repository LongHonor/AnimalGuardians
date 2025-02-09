﻿#include "gameBoardHandler.h"
#include "globalVariable.h"
#include "pcHandler.h"
#include "npcModule.h"
#include <windows.h>
#include <stdio.h>
#include <time.h>

//void initGameBoard() {
//	int posX, posY;
//	for (posY = 0; posY < gBoardHeight + 3; posY++) {
//		gameBoardInfo[posY][0] = 1;
//		gameBoardInfo[posY][gBoardWidth + 1] = 1;
//	}
//	for (posX = 0; posX < gBoardWidth + 2; posX++) {
//		gameBoardInfo[gBoardHeight][posX] = 1;
//	}
//}

void drawGameBoard() {
	int posX, posY;
	int pcAreaLine = 19;

	//setCurrentGameBoard(0);

	for (posY = 0; posY < gBoardHeight + 3; posY++) {
		setCurrentCursorPos(0, posY);
		if (posY == gBoardHeight + 2) printf("└");
		else if (posY == 0) printf("┌");
		else if (posY == pcAreaLine) printf("├");
		else printf("│");
		setCurrentCursorPos((gBoardWidth + 1) * 2, posY);
		if (posY == gBoardHeight + 2) printf("┘");
		else if (posY == 0) printf("┐");
		else if (posY == pcAreaLine) printf("┤");
		else printf("│");

		for (posX = 1; posX < gBoardWidth + 1; posX++) {
			if (currentGameBoard[posY][posX] == 1|| currentGameBoard[posY][posX] == 2) {
				setCurrentCursorPos(posX * 2, posY);
				printf("─");
			}
		}
	}
	changeConsoleColor(green);
	for (posY = 0; posY < gBoardHeight + 3; posY++) {
		for (posX = 1; posX < gBoardWidth + 1; posX++) {
			if (currentGameBoard[posY][posX] == 4) {
				setCurrentCursorPos(posX * 2, posY);
				printf("♣");
			}
		}
	}
	changeConsoleColor(gray);
	for (posY = 0; posY < gBoardHeight + 3; posY++) {
		for (posX = 1; posX < gBoardWidth + 1; posX++) {
			if (currentGameBoard[posY][posX] == 5) {
				setCurrentCursorPos(posX * 2, posY);
				printf("■");
			}
		}
	}
	restoreConsoleColor();
	for (posY = 0; posY < gBoardHeight + 3; posY++) {
		for (posX = 1; posX < gBoardWidth + 1; posX++) {
			if (currentGameBoard[posY][posX] == 7) {
				setCurrentCursorPos(posX * 2, posY);
				printf("□");
			}
		}
	}
	setCurrentCursorPos(10, 19);
}

//좌표를 인자로 받아 gameBoardInfo에 추가
void AddBlockToBoard(posStruct barricadeCurPos) {

	int x, y, arrCurX, arrCurY;
	arrCurX = (barricadeCurPos.X - gBoardOx) / 2;
	arrCurY = barricadeCurPos.Y - gBoardOy;
	for (y = 0; y < 1; y++)
	{
		for (x = 0; x < 3; x++)
		{
			currentGameBoard[arrCurY + y][arrCurX + x] = 7;
		}
	}
}


void drawAnimal() {
	int posX;
	int arrX,arrY;
	changeConsoleColor(purple);
	for (int i = 0; i < 3; i++) {
		if (animalArray[i].activeStatus == TRUE) {
			//animalNPC 위치 받아와서 setCurrentCursorPos()호출
			posStruct animalCurPos = getAnimalCurrentPos(&animalArray[i]);
			arrX = (animalCurPos.X - gBoardOx);
			arrY = (animalCurPos.Y - gBoardOy);
			for (posX = 0; posX < 2; posX++) {
				setCurrentCursorPos(arrX*2 + posX * 2, animalCurPos.Y);
				
				if (animalModel[0][posX] == 1) printf("♧");
				else printf("■");
				currentGameBoard[arrY][arrX + posX] = 3;
			}
		}
	}
	restoreConsoleColor();
}
void deleteAnimal() {
	int posX;
	int arrX, arrY;
	for (int i = 0; i < 3; i++) {

		if (animalArray[i].activeStatus == TRUE) {
			//animalNPC 위치 받아와서 setCurrentCursorPos()호출
			posStruct animalCurPos = getAnimalCurrentPos(&animalArray[i]);
			arrX = (animalCurPos.X - gBoardOx);
			arrY = (animalCurPos.Y - gBoardOy);
			for (posX = 0; posX < 2; posX++) {
				setCurrentCursorPos(arrX * 2 + posX * 2, animalCurPos.Y);
				printf("  ");
				currentGameBoard[arrY][arrX + posX] = 0;
			}
		}
		else continue;
	}
}


void drawKing() {
	int posX, posY;
	int arrX, arrY;
	arrX = (king.pos.X - gBoardOx) / 2;
	arrY = (king.pos.Y - gBoardOy);
	changeConsoleColor(purple);
	for (posX = 0; posX < 4; posX++) {
		for (posY = 0; posY < 2; posY++) {
			setCurrentCursorPos(king.pos.X + posX * 2, king.pos.Y + posY);
			if (kingAnimalModel[0][posY][posX] == 1) printf("■");
			else if (kingAnimalModel[0][posY][posX] == 2) printf("▲");
			else printf("  ");
			currentGameBoard[arrY + posY][arrX] = 3;
		}
	}
	restoreConsoleColor();
}
void deleteKing() {
	int posX, posY;
	int arrX, arrY;

	arrX = (king.pos.X - gBoardOx) / 2;
	arrY = (king.pos.Y - gBoardOy);
	for (posX = 0; posX < 4; posX++) {
		for (posY = 0; posY < 2; posY++) {
			setCurrentCursorPos(king.pos.X + posX * 2, king.pos.Y + posY);
			printf("  ");
			currentGameBoard[arrY + posY][arrX] = 0;
		}
	}

}


void drawDieAnimalEffect(posStruct animalCurPos) {
	int posX;
	int arrX, arrY;

	arrX = (animalCurPos.X - gBoardOx);
	arrY = (animalCurPos.Y - gBoardOy);

	changeConsoleColor(red);
	for (posX = 0; posX < 2; posX++) {
		setCurrentCursorPos(animalCurPos.X*2 + posX * 2, animalCurPos.Y);
		printf("※");
		currentGameBoard[arrY][arrX + posX] = 0;
	}
	restoreConsoleColor();
}
void deleteDieAnimalEffect() {
	int posX;
	int arrX, arrY;

	for (int i = 0; i < 3; i++) {

		if (animalArray[i].activeStatus == FALSE) {
			posStruct animalCurPos = getAnimalCurrentPos(&animalArray[i]);
			arrX = (animalCurPos.X - gBoardOx);
			arrY = (animalCurPos.Y - gBoardOy);

			for (posX = 0; posX < 2; posX++) {
				setCurrentCursorPos(animalCurPos.X*2 + posX * 2, animalCurPos.Y);
				printf("  ");
				
			}
		}
	}
}


void drawEnemy() {
	int posY;
	int arrX, arrY;

	enemyNPC * search = enemyList->enemyHeader;


	while (search != NULL) {
		if (search->activeStatus == TRUE) {
			posStruct enemyCurPos = getEnemyCurrentPos(search->id);
			arrX = (enemyCurPos.X - gBoardOx) / 2;
			arrY = (enemyCurPos.Y - gBoardOy);
			//enemyNPC 위치 받아와서 setCurrentCursorPos()호출

			if (search->type == 2) changeConsoleColor(1);
			else if (search->type == 3)changeConsoleColor(12);
			else changeConsoleColor(red);

			for (posY = 0; posY < 1; posY++) {
				setCurrentCursorPos(enemyCurPos.X, enemyCurPos.Y + posY);
				
				if (enemyModel[posY][0] == 1) printf("▼");
				else printf("▲");
				currentGameBoard[arrY + posY][arrX] = 6;
			}
		}
		search = search->next;
	}
	restoreConsoleColor();
	
}
void deleteEnemy() {
	int posY;
	int arrX, arrY;

	enemyNPC * search = enemyList->enemyHeader;
	
	while (search != NULL) {
		if (search->activeStatus == TRUE) {
			posStruct enemyCurPos = getEnemyCurrentPos(search->id);
			//enemyNPC 위치 받아와서 setCurrentCursorPos()호출
			arrX = (enemyCurPos.X - gBoardOx) / 2;
			arrY = (enemyCurPos.Y - gBoardOy);

			for (posY = 0; posY < 1; posY++) {
				setCurrentCursorPos(enemyCurPos.X, enemyCurPos.Y + posY);
				printf("  ");
				currentGameBoard[arrY + posY][arrX] = 0;
			}


		}
		search = search->next;
	}
	
}


void drawBoss() {
	int posX, posY;
	int arrX, arrY;
	
	arrX = (boss.pos.X - gBoardOx) / 2;
	arrY = (boss.pos.Y - gBoardOy);
	for (posX = 0; posX < 4; posX++) {
		for (posY = 0; posY < 4; posY++) {
			setCurrentCursorPos(boss.pos.X + posX * 2, boss.pos.Y+ posY);
			if (boss.hp > 5) {
				if (bossEnemyModel[posY][posX] == 2) printf("※");
				else printf("■");
			}
			else {
				if (bossEnemyModel[posY][posX] == 2) printf("※");
				else printf("▒");
			}
			currentGameBoard[arrY + posY][arrX + posX] = 8;
		}
	}


}
void deleteBoss() {
	int posX, posY;
	int arrX, arrY;

	arrX = (boss.pos.X - gBoardOx) / 2;
	arrY = (boss.pos.Y - gBoardOy);
	for (posX = 0; posX < 4; posX++) {
		for (posY = 0; posY < 4; posY++) {
			setCurrentCursorPos(boss.pos.X + posX * 2, boss.pos.Y+posY);
			printf("  ");
			currentGameBoard[arrY + posY][arrX + posX] = 0;
		}
	}


}


void drawDieEnemyEffect(posStruct enemyCurPos) {
	int posX, posY;
	int arrX, arrY;

	enemyNPC * search = enemyList->enemyHeader;
	arrX = (enemyCurPos.X - gBoardOx) / 2;
	arrY = (enemyCurPos.Y - gBoardOy);

	for (posY = 0; posY < 1; posY++) {
		setCurrentCursorPos(enemyCurPos.X, enemyCurPos.Y + posY - 1);
		printf("  ");
		currentGameBoard[arrY + posY - 1][arrX] = -1;
	}
	setCurrentCursorPos(enemyCurPos.X - 2, enemyCurPos.Y - 2);
	for (posY = 0; posY < 3; posY++) {
		for (posX = 0; posX < 3; posX++) {
			setCurrentCursorPos(enemyCurPos.X - 2 + posX * 2, enemyCurPos.Y - 2 + posY);
			if (currentGameBoard[arrY-2+posY][arrX-1+posX] == 0) printf("※");	
		}
	}
	currentGameBoard[arrY - 1][arrX] = 0;
}
void deleteDieEnemyEffect() {
	int posX, posY;
	int arrX, arrY;

	posStruct enemyCurPos;
	enemyNPC * search = enemyList->enemyHeader;
	
	while (search != NULL) {
		if (search->activeStatus == FALSE && search->dieFlag==FALSE) {
			if ((double)(clock() - search->deadTime) / CLOCKS_PER_SEC >= dieTime) {
				search->dieFlag = TRUE;
				enemyCurPos.X = search->deadPos.X;
				enemyCurPos.Y = search->deadPos.Y;
				arrX = (enemyCurPos.X - gBoardOx) / 2;
				arrY = (enemyCurPos.Y - gBoardOy);
				setCurrentCursorPos(enemyCurPos.X - 2, enemyCurPos.Y - 1);
				for (posY = 0; posY < 3; posY++) {
					for (posX = 0; posX < 3; posX++) {
						setCurrentCursorPos(enemyCurPos.X - 2 + posX * 2, enemyCurPos.Y - 1 + posY);
						if (currentGameBoard[arrY - 1 + posY][arrX - 1 + posX] == 0) printf("  ");
					}
				}
			}
		}
		search = search->next;
	}
}

void drawInitialUI() {
	printBulletCount();
	printEnemyCount();
	printCurrentItem();
}

void printBulletCount() {
	//pcHandler에서 불러오는 구조
	int bulletCnt = bulletCount;

	setCurrentCursorPos(44 * 2, 3);
	printf("Bullet : %2d / %2d", bulletCnt, maxBullet);
}
void printEnemyCount() {
	int enemyTotalCnt = allEnemyCount;

	setCurrentCursorPos(44 * 2, 4);
	//총 enemy 수와 현재 enemy수 
	printf("Enemy  : %2d / %2d", currentEnemyCount, enemyTotalCnt);
}

