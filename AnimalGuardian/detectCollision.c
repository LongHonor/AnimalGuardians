﻿#include "detectCollision.h"
#include "globalVariable.h"

extern char gameBoardInfo[23][42];

//enemyNPC 충돌 관리
int enemyNPCDetectCollision(int posX, int posY) {
	int arrY = posY - gBoardOy;
	{
		for (y = 0; y < 2; y++)
		{
			if (enemyModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] != 0) {
				return 0;
			}
		}
	}