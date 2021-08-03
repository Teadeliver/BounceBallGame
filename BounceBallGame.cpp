#include"GAME.h"

int map[19][7] = {-1};//砖块的地图
int ballX, ballY;//球圆心的坐标
int ballRadius;//球半径
int boardX, boardY;//板左上角的坐标
int boardWidth, boardHigh;//板的宽和高
int brickWidth, brickHigh;//砖块的宽和高
int width, high;//画面的宽和高
int moveX, moveY;//球的移动速度
int come = 0;
HWND hwnd;
FILE* fp = NULL;
PLAYER* player = NULL;
time_t start, end;
int main()
{
	char ch;
	int flag = 0;					//进入游戏的标志
	time_t first, second;

	startup();
	while (1)
	{
		ch = Getchoice();
		switch (ch)
		{
		case 59:					//F1
		{
			BeginBatchDraw();
			show();
			Sleep(2000);
			start = time(NULL);
			first = time(NULL);
			second = time(NULL);
			updateWithoutInput();
			updateWithInput();
			while (1)
			{
				second = time(NULL);
				if (difftime(second, first) == 5)
				{
					updateShow();//更新砖块数据
					first = time(NULL);
				}
				show();
				updateWithoutInput();
				updateWithInput();
			}
			flag = 1;
			break;
		}
		case 60:					//F2
		{
			ScorePrint(0);
			WelcomPage();
			break;
		}
		case 61:					//F3
		{
			HelpPage();				//帮助页面
			WelcomPage();
			break;
		}
		case 62:					//F4
		{
			AboutPage();			//关于页面
			WelcomPage();
			break;
		}
		case 63:					//F5
			exit(EXIT_SUCCESS);		//退出
			break;
		default:
			break;
		}
		if (flag == 1)
		{
			break;
		}
	}
	return 0;
}
