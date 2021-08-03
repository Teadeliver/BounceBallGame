#include"GAME.h"

//与用户输入无关的更新
void updateWithoutInput()
{
	//球的移动
	ballX += moveX;
	ballY += moveY;

	//球撞上方的砖块反弹
	for (int i = 0; i < 17; i++)
	{
		if (ballY - ballRadius == i * brickHigh)
		{
			//搜索小球上方砖块的下标
			int brick_j = (ballX - ballRadius) / brickWidth;//列下标
			int brick_i = (ballY - ballRadius) / brickHigh - 1;//行下标
			//判断球的上方是否存在砖块
			if (map[brick_i][brick_j] != -1)
			{
				moveY = -moveY;
				map[brick_i][brick_j] = -1;//让砖块消失

				player->scoreNow++;
			}
			break;
		}
	}

	//球碰旁边的砖块反弹
	if (ballY - ballRadius < 3 * brickHigh)
	{
		//撞左边的砖块
		if (ballX - ballRadius == brickWidth * 1 ||
			ballX - ballRadius == brickWidth * 2 ||
			ballX - ballRadius == brickWidth * 3 ||
			ballX - ballRadius == brickWidth * 4)
		{
			//搜索小球左边砖块的下标
			int brick_j = (ballX - ballRadius) / brickWidth - 1;//列下标
			int brick_i = (ballY - ballRadius) / brickHigh;//行下标
			if (map[brick_i][brick_j] != -1)
			{
				moveX = -moveX;
				map[brick_i][brick_j] = -1;//让砖块消失
				player->scoreNow++;
			}
		}

		//撞右边的砖块
		for (int i = 0; i < 17; i++)
		{
			if (ballX + ballRadius == brickWidth * 1 ||
				ballX + ballRadius == brickWidth * 2 ||
				ballX + ballRadius == brickWidth * 3 ||
				ballX + ballRadius == brickWidth * 4)
			{
				//搜索小球右边砖块的下标
				int brick_j = (ballX - ballRadius) / brickWidth + 1;//列下标
				int brick_i = (ballY - ballRadius) / brickHigh;//行下标
				if (map[brick_i][brick_j] != -1)
				{
					moveX = -moveX;
					map[brick_i][brick_j] = -1;//让砖块消失

					player->scoreNow++;
				}
			}
		}
	}

	//球撞下方的砖块反弹
	for (int i = 1; i < 17; i++)
	{
		if (ballY + ballRadius == i * brickHigh)
		{
			//搜索小球下方砖块的下标
			int brick_j = (ballX - ballRadius) / brickWidth;//列下标
			int brick_i = ((ballY + ballRadius) / brickHigh) + 1;//行下标
			//判断球的下方是否存在砖块
			if (map[brick_i][brick_j] != -1)
			{
				moveY = -moveY;
				map[brick_i][brick_j] = -1;//让砖块消失

				player->scoreNow++;
			}
			break;
		}
	}
	//球碰到上墙壁反弹
	if (ballY - ballRadius <= 0)
	{
		moveY = -moveY;
	}

	//球碰到左右墙壁反弹
	if (ballX - ballRadius <= 0 || ballX + ballRadius >= width)
	{
		moveX = -moveX;
	}
	//球碰到木板反弹
	if (ballY + ballRadius == boardY)
	{
		if (ballX >= boardX && ballX <= boardX + boardWidth)
		{
			moveY = -moveY;
		}
	}

	//判断胜负
	gameOver();
}
//与用户输入有关的更新
void updateWithInput()
{
	//按键处理
	if (_kbhit())
	{
		char hit = _getch();
		switch (hit)
		{
		case 'a'://左移
		case 'A':
		case 75:
			boardX -= 25;
			if (boardX < 0)
			{
				boardX = 0;
			}
			break;
		case 'd'://右移
		case 'D':
		case 77:
			boardX += 25;
			if (boardX + boardWidth > width)
			{
				boardX = width - boardWidth;
			}
			break;
		case ' '://暂停
		case '\r':
		case 27:
			while (_getch() != ' ' && _getch() != '\r' && _getch() != 27);
			break;
		}
	}
}
//判断胜负，结束游戏
void gameOver()
{
	//判断负
	int flag = 0;
	for (int i = 0; i < 5; i++)
	{
		if (map[18][i] != -1)
		{
			flag = 1;
		}
	}
	if (ballY - ballRadius > high || flag == 1)
	{
		//计时结束
		end = time(NULL);
		player->time += (int)difftime(end, start);

		LOGFONT f;
		gettextstyle(&f);						// 获取当前字体设置
		f.lfHeight = 20;						// 设置字体高度为 20
		_tcscpy(f.lfFaceName, _T("楷体"));		// 设置字体为“黑体”
		f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
		settextstyle(&f);						// 设置字体样式
		outtextxy(210, high / 2, "YOU LOSE!");
		Sleep(2000);

		char mestr[50];
		_stprintf(mestr, _T("你的分数是 %d"), player->scoreNow);
		outtextxy(190, 400, mestr);
		moveY = -moveY;
		EndBatchDraw();
		Sleep(2000);
		ScoreSave();
		ScorePrint(1);
		Sleep(10000);
		closegraph();
		exit(-1);//结束游戏
	}
}

void updateShow()
{
	srand((unsigned)time(NULL));
	for (int i = 17; i >= 0; i--)
	{
		for (int j = 4; j >= 0; j--)
		{
			map[i + 1][j] = map[i][j];
		}
	}
	for (int j = 0; j < 5; j++)
	{
		map[0][j] = rand() % 6 + 1;
		while (map[0][j] == map[1][j] || map[0][j] == map[0][j + 1])
		{
			map[0][j] = rand() % 6 + 1;
			if (j != 0)
			{
				while (map[0][j] == map[1][j] || map[0][j] == map[0][j + 1])
				{
					map[0][j] = rand() % 6 + 1;
				}
			}
		}
	}
}

int Getchoice()
{
	int ch;

	do
	{
		ch = _getch();
	} while (ch != 59 && ch != 60
		&& ch != 61 && ch != 62 && ch != 63);
	/*
		59： F1
		60： F2
		61： F3
		62： F4
		63： F5
	*/

	return ch;
}