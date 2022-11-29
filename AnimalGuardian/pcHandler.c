﻿#include "pcHandler.h"
#include "globalVariable.h"
#include "gameItem.h"
#include "gameBoardHandler.h"
#include "detectCollision.h"
#include <stdio.h>
#include <conio.h>
//PC 초기화
PC player = { {40,20},1,200,3 };

//bullet 초기화
int bulletCount = 10;
Bullet* bullet_head = NULL;
int bulletItem = 0;

loadFlag = 0;

void showPC(PC player) {
	setCurrentCursorPos(player.pos.X, player.pos.Y);
	printf("●");
	setCurrentCursorPos(player.pos.X, player.pos.Y);    //cursor위치 처음 위치로 다시 설정
}

void erasePC(PC player) {
	setCurrentCursorPos(player.pos.X, player.pos.Y);
	printf("  ");
	setCurrentCursorPos(player.pos.X, player.pos.Y);    //cursor위치 처음 위치로 다시 설정
}

void showBullet(posStruct pos) {
	setCurrentCursorPos(pos.X, pos.Y);
	printf("ο");
}
void eraseBullet(posStruct pos) {
	setCurrentCursorPos(pos.X, pos.Y);
	printf("  ");
}

void shiftLeftPc() {
	if (!detectCollisionPC(player.pos.X - 2, player.pos.Y)) {
		return;
	}
	erasePC(player);
	player.pos.X -= 2;
	setCurrentCursorPos(player.pos.X, player.pos.Y);
	showPC(player);
}
void shiftRightPc() {
	if (!detectCollisionPC(player.pos.X + 2, player.pos.Y)) {
		return;
	}
	erasePC(player);
	player.pos.X += 2;
	setCurrentCursorPos(player.pos.X, player.pos.Y);
	showPC(player);
}
void shootBullet() {
	Bullet* curr = bullet_head;
	Bullet* first_bullet = bullet_head;
	while (1) {
		if (curr == NULL) {
			curr = first_bullet;
		}
		//일반 모드
		if (bulletItem == 0) {
			if (!detectCollisionBullet(curr->pos.X, curr->pos.Y - 1)) {
				first_bullet = curr->link;
			}
			else if (!detectCollisionBullet(curr->pos.X, curr->pos.Y - 2)) {
				curr->pos.Y -= 1;
				showBullet(curr->pos);
				Sleep(curr->speed);
				eraseBullet(curr->pos);
			}
			else {
				curr->pos.Y -= 2;
				showBullet(curr->pos);
				Sleep(curr->speed);
				eraseBullet(curr->pos);
			}
		}
		//관통 모드
		else if (bulletItem == 1) {
			curr->pos.Y -= 2;
			if (detectCollisionBullet(curr->pos.X, curr->pos.Y)) {
				showBullet(curr->pos);
				Sleep(curr->speed);
				eraseBullet(curr->pos);
			}
			else {
				Sleep(curr->speed);
			}
		}
		if (_kbhit() != 0) {
			int key = _getch();
			switch (key) {
			case left:
				shiftLeftPc();
				break;
			case right:
				shiftRightPc();
				break;
			case space:
				if (bulletCount > 0) {
					Bullet* newbullet = (Bullet*)malloc(sizeof(Bullet));
					newbullet->pos = player.pos;
					newbullet->speed = 15;
					newbullet->link = NULL;
					curr->link = newbullet;
					bulletCount--;
				}
				break;
			}
		}
		if (curr->pos.Y < gBoardOy + 2) {
			first_bullet = curr->link;
			free(curr);
		}
		if (first_bullet == NULL) {
			break;
		}
		curr = curr->link;
	}
}
void loadBullet() {
	bulletCount = 10;
}
void pcKeyInput() {
	int key;
	for (int i = 0; i < 20; i++) {
		//_kbhit 은 입력시 1 리턴
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case left:
				shiftLeftPc();
				break;
			case right:
				shiftRightPc();
				break;
			case space:
				if (bulletCount > 0) {
					Bullet* newbullet = (Bullet*)malloc(sizeof(Bullet));
					newbullet->pos = player.pos;
					newbullet->speed = 15;
					newbullet->link = NULL;
					bullet_head = newbullet;
					bulletCount--;
					shootBullet();
				}
				break;
			case load:
				loadBullet();
				checkLoadStartTime = clock();
				loadFlag = 1;
				break;
			case item:
				placeBarricade();
				drawGameBoard();
				//아이템 종류당 번호 할당
				//번호에 해당하는 아이템 사용
				break;
			}
		}
		Sleep(20);
	}
}