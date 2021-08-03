#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
# include <stdio.h>
# include <graphics.h>
# include <conio.h>
# include <time.h>
# include <windef.h>
# include <assert.h>
# include <windows.h>
# include <tuple>
# include <ctime>
# include <stdio.h>

typedef struct
{
	char name[11];//储存玩家昵称
	int scoreNow;//本局游戏分数
	int frequency;//游戏次数
	int ranking;//排名
	int highScore;//历史最高分
	int time;//游戏总时长
}PLAYER;
extern PLAYER* player;
extern int map[19][7];//砖块的地图
extern int ballX, ballY;//球圆心的坐标
extern int ballRadius;//球半径
extern int boardX, boardY;//板左上角的坐标
extern int boardWidth, boardHigh;//板的宽和高
extern int brickWidth, brickHigh;//砖块的宽和高
extern int width, high;//画面的宽和高
extern int moveX, moveY;//球的移动速度
extern int come;
extern FILE* fp;
extern HWND hwnd;
extern time_t start, end;

//函数声明部分
void startup();
void show();
void updateWithoutInput();
void updateWithInput();
void drawBrickMap();
void gameOver();
void ScoreSave();
void ScoreSort();
void ScorePrint(int);
void WelcomPage();
void AboutPage();
void HelpPage();
int Getchoice();
void updateShow();