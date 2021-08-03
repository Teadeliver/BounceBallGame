#include"GAME.h"

//开始菜单界面
void WelcomPage()
{
	setbkcolor(RGB(56, 142, 142));				//设置背景色
	cleardevice();								//刷新背景

	settextcolor(WHITE);
	settextstyle(60, 0, _T("黑体"));
	outtextxy(135, 80, _T("弹 力 球"));

	setfillcolor(RGB(255, 239, 219));			//设置填充颜色
	solidroundrect(180, 250, 320, 290, 10, 10);	//开始游戏选项
	solidroundrect(180, 300, 320, 340, 10, 10);	//排行榜
	solidroundrect(180, 350, 320, 390, 10, 10);	//帮助选项
	solidroundrect(180, 400, 320, 440, 10, 10);	//关于选项
	solidroundrect(180, 450, 320, 490, 10, 10); //退出选项

	setbkcolor(RGB(255, 239, 219));				//设置文字的背景色
	setbkmode(OPAQUE);							//文字输出时的背景模式（背景用当前背景色填充）
	settextcolor(RED);							//设置文字颜色
	
	//抗锯齿显示文字，效果更好
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 20;						// 设置字体高度为 20
	_tcscpy(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式

	outtextxy(200, 260, _T("开始游戏 F1"));			//打印选项
	outtextxy(200, 310, _T("排行榜   F2"));
	outtextxy(200, 360, _T("帮助     F3"));
	outtextxy(200, 410, _T("关于     F4"));
	outtextxy(200, 460, _T("退出     F5"));
}

//初始化数据
void startup()
{
	//初始化该轮玩家的分数
	player = (PLAYER*)malloc(sizeof(PLAYER));
	if (player)
	{
		player->scoreNow = 0;
		player->frequency = 1;
		player->time = 0;
	}

	srand((unsigned)time(NULL));
	//画面尺寸
	width = 100 * 5;//500
	high = 700;
	//砖块的尺寸
	brickWidth = 100;
	brickHigh = 40;
	//木板尺寸
	boardWidth = 100;
	boardHigh = 20;
	boardX = width / 2 - boardWidth / 2;
	boardY = high - boardHigh;
	//球的位置
	ballRadius = 10;
	ballX = rand() % 47 * 10 + ballRadius;//20~480
	ballY = brickHigh * 3 + ballRadius;
	//球的移动速度
	moveX = 10;
	moveY = 10;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			map[i][j] = -1;
		}
	}
	//使代表砖块的颜色的数字随机，即有5种颜色
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			map[i][j] = rand() % 6 + 1;
			if (i == 0 && j != 0)
			{
				if (map[i][j] == map[i][j - 1])
				{
					do {
						map[i][j] = rand() % 6 + 1;
					} while (map[i][j] == map[i][j - 1]);
				}
			}
			else if (i != 0 && j != 0)
			{
				if (map[i][j] == map[i][j - 1] || map[i][j] == map[i - 1][j])
				{
					do {
						map[i][j] = rand() % 6 + 1;
					} while (map[i][j] == map[i][j - 1] || map[i][j] == map[i - 1][j]);
				}
			}
			if (i > 0 && j == 0)
			{
				if (map[i][j] == map[i - 1][j])
				{
					do {
						map[i][j] = rand() % 6 + 1;
					} while (map[i][j] == map[i - 1][j]);
				}
			}
		}
	}
	//初始化画面尺寸
	hwnd = initgraph(width, high);
	WelcomPage();
	//设置画面背景颜色
	setbkcolor(RGB(240, 237, 220));
}

//画砖块
void drawBrickMap()
{
	int i, j;
	int brickX, brickY;
	for (i = 0; i < 17; i++)
	{
		for (j = 0; j < 5; j++)
		{
			brickX = j * brickWidth;
			brickY = i * brickHigh;
			switch (map[i][j])
			{
			case 0:
				setfillcolor(RGB(112, 207, 166));
				solidrectangle(brickX, brickY, brickX + brickWidth, brickY + brickHigh);
				break;
			case 1:
				setfillcolor(RGB(203, 58, 87));
				solidrectangle(brickX, brickY, brickX + brickWidth, brickY + brickHigh);
				break;
			case 2:
				setfillcolor(RGB(202, 105, 36));
				solidrectangle(brickX, brickY, brickX + brickWidth, brickY + brickHigh);
				break;
			case 3:
				setfillcolor(RGB(186, 206, 195));
				solidrectangle(brickX, brickY, brickX + brickWidth, brickY + brickHigh);
				break;
			case 4:
				setfillcolor(RGB(217, 182, 18));
				solidrectangle(brickX, brickY, brickX + brickWidth, brickY + brickHigh);
				break;
			case 5:
				setfillcolor(RGB(23, 124, 176));
				solidrectangle(brickX, brickY, brickX + brickWidth, brickY + brickHigh);
				break;
			case 6:
				setfillcolor(RGB(204, 164, 227));
				solidrectangle(brickX, brickY, brickX + brickWidth, brickY + brickHigh);
				break;
			case -1:
				break;
			}
		}
	}
}


//展示画面
void show()
{
	//刷新画面
	cleardevice();

	//画砖块图
	drawBrickMap();

	//画木板
	setfillcolor(RGB(117, 135, 139));
	solidrectangle(boardX, boardY, boardX + boardWidth, boardY + boardY + boardHigh);

	//画圆
	setfillcolor(RGB(66, 75, 80));
	solidcircle(ballX, ballY, ballRadius);

	FlushBatchDraw();
	Sleep(40);
}