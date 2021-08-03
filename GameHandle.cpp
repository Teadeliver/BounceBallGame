#include"GAME.h"

//���û������޹صĸ���
void updateWithoutInput()
{
	//����ƶ�
	ballX += moveX;
	ballY += moveY;

	//��ײ�Ϸ���ש�鷴��
	for (int i = 0; i < 17; i++)
	{
		if (ballY - ballRadius == i * brickHigh)
		{
			//����С���Ϸ�ש����±�
			int brick_j = (ballX - ballRadius) / brickWidth;//���±�
			int brick_i = (ballY - ballRadius) / brickHigh - 1;//���±�
			//�ж�����Ϸ��Ƿ����ש��
			if (map[brick_i][brick_j] != -1)
			{
				moveY = -moveY;
				map[brick_i][brick_j] = -1;//��ש����ʧ

				player->scoreNow++;
			}
			break;
		}
	}

	//�����Աߵ�ש�鷴��
	if (ballY - ballRadius < 3 * brickHigh)
	{
		//ײ��ߵ�ש��
		if (ballX - ballRadius == brickWidth * 1 ||
			ballX - ballRadius == brickWidth * 2 ||
			ballX - ballRadius == brickWidth * 3 ||
			ballX - ballRadius == brickWidth * 4)
		{
			//����С�����ש����±�
			int brick_j = (ballX - ballRadius) / brickWidth - 1;//���±�
			int brick_i = (ballY - ballRadius) / brickHigh;//���±�
			if (map[brick_i][brick_j] != -1)
			{
				moveX = -moveX;
				map[brick_i][brick_j] = -1;//��ש����ʧ
				player->scoreNow++;
			}
		}

		//ײ�ұߵ�ש��
		for (int i = 0; i < 17; i++)
		{
			if (ballX + ballRadius == brickWidth * 1 ||
				ballX + ballRadius == brickWidth * 2 ||
				ballX + ballRadius == brickWidth * 3 ||
				ballX + ballRadius == brickWidth * 4)
			{
				//����С���ұ�ש����±�
				int brick_j = (ballX - ballRadius) / brickWidth + 1;//���±�
				int brick_i = (ballY - ballRadius) / brickHigh;//���±�
				if (map[brick_i][brick_j] != -1)
				{
					moveX = -moveX;
					map[brick_i][brick_j] = -1;//��ש����ʧ

					player->scoreNow++;
				}
			}
		}
	}

	//��ײ�·���ש�鷴��
	for (int i = 1; i < 17; i++)
	{
		if (ballY + ballRadius == i * brickHigh)
		{
			//����С���·�ש����±�
			int brick_j = (ballX - ballRadius) / brickWidth;//���±�
			int brick_i = ((ballY + ballRadius) / brickHigh) + 1;//���±�
			//�ж�����·��Ƿ����ש��
			if (map[brick_i][brick_j] != -1)
			{
				moveY = -moveY;
				map[brick_i][brick_j] = -1;//��ש����ʧ

				player->scoreNow++;
			}
			break;
		}
	}
	//��������ǽ�ڷ���
	if (ballY - ballRadius <= 0)
	{
		moveY = -moveY;
	}

	//����������ǽ�ڷ���
	if (ballX - ballRadius <= 0 || ballX + ballRadius >= width)
	{
		moveX = -moveX;
	}
	//������ľ�巴��
	if (ballY + ballRadius == boardY)
	{
		if (ballX >= boardX && ballX <= boardX + boardWidth)
		{
			moveY = -moveY;
		}
	}

	//�ж�ʤ��
	gameOver();
}
//���û������йصĸ���
void updateWithInput()
{
	//��������
	if (_kbhit())
	{
		char hit = _getch();
		switch (hit)
		{
		case 'a'://����
		case 'A':
		case 75:
			boardX -= 25;
			if (boardX < 0)
			{
				boardX = 0;
			}
			break;
		case 'd'://����
		case 'D':
		case 77:
			boardX += 25;
			if (boardX + boardWidth > width)
			{
				boardX = width - boardWidth;
			}
			break;
		case ' '://��ͣ
		case '\r':
		case 27:
			while (_getch() != ' ' && _getch() != '\r' && _getch() != 27);
			break;
		}
	}
}
//�ж�ʤ����������Ϸ
void gameOver()
{
	//�жϸ�
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
		//��ʱ����
		end = time(NULL);
		player->time += (int)difftime(end, start);

		LOGFONT f;
		gettextstyle(&f);						// ��ȡ��ǰ��������
		f.lfHeight = 20;						// ��������߶�Ϊ 20
		_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
		f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
		settextstyle(&f);						// ����������ʽ
		outtextxy(210, high / 2, "YOU LOSE!");
		Sleep(2000);

		char mestr[50];
		_stprintf(mestr, _T("��ķ����� %d"), player->scoreNow);
		outtextxy(190, 400, mestr);
		moveY = -moveY;
		EndBatchDraw();
		Sleep(2000);
		ScoreSave();
		ScorePrint(1);
		Sleep(10000);
		closegraph();
		exit(-1);//������Ϸ
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
		59�� F1
		60�� F2
		61�� F3
		62�� F4
		63�� F5
	*/

	return ch;
}