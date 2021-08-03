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
	char name[11];//��������ǳ�
	int scoreNow;//������Ϸ����
	int frequency;//��Ϸ����
	int ranking;//����
	int highScore;//��ʷ��߷�
	int time;//��Ϸ��ʱ��
}PLAYER;
extern PLAYER* player;
extern int map[19][7];//ש��ĵ�ͼ
extern int ballX, ballY;//��Բ�ĵ�����
extern int ballRadius;//��뾶
extern int boardX, boardY;//�����Ͻǵ�����
extern int boardWidth, boardHigh;//��Ŀ�͸�
extern int brickWidth, brickHigh;//ש��Ŀ�͸�
extern int width, high;//����Ŀ�͸�
extern int moveX, moveY;//����ƶ��ٶ�
extern int come;
extern FILE* fp;
extern HWND hwnd;
extern time_t start, end;

//������������
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