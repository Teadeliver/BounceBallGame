#include"GAME.h"

//��ʼ�˵�����
void WelcomPage()
{
	setbkcolor(RGB(56, 142, 142));				//���ñ���ɫ
	cleardevice();								//ˢ�±���

	settextcolor(WHITE);
	settextstyle(60, 0, _T("����"));
	outtextxy(135, 80, _T("�� �� ��"));

	setfillcolor(RGB(255, 239, 219));			//���������ɫ
	solidroundrect(180, 250, 320, 290, 10, 10);	//��ʼ��Ϸѡ��
	solidroundrect(180, 300, 320, 340, 10, 10);	//���а�
	solidroundrect(180, 350, 320, 390, 10, 10);	//����ѡ��
	solidroundrect(180, 400, 320, 440, 10, 10);	//����ѡ��
	solidroundrect(180, 450, 320, 490, 10, 10); //�˳�ѡ��

	setbkcolor(RGB(255, 239, 219));				//�������ֵı���ɫ
	setbkmode(OPAQUE);							//�������ʱ�ı���ģʽ�������õ�ǰ����ɫ��䣩
	settextcolor(RED);							//����������ɫ
	
	//�������ʾ���֣�Ч������
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 20
	_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ

	outtextxy(200, 260, _T("��ʼ��Ϸ F1"));			//��ӡѡ��
	outtextxy(200, 310, _T("���а�   F2"));
	outtextxy(200, 360, _T("����     F3"));
	outtextxy(200, 410, _T("����     F4"));
	outtextxy(200, 460, _T("�˳�     F5"));
}

//��ʼ������
void startup()
{
	//��ʼ��������ҵķ���
	player = (PLAYER*)malloc(sizeof(PLAYER));
	if (player)
	{
		player->scoreNow = 0;
		player->frequency = 1;
		player->time = 0;
	}

	srand((unsigned)time(NULL));
	//����ߴ�
	width = 100 * 5;//500
	high = 700;
	//ש��ĳߴ�
	brickWidth = 100;
	brickHigh = 40;
	//ľ��ߴ�
	boardWidth = 100;
	boardHigh = 20;
	boardX = width / 2 - boardWidth / 2;
	boardY = high - boardHigh;
	//���λ��
	ballRadius = 10;
	ballX = rand() % 47 * 10 + ballRadius;//20~480
	ballY = brickHigh * 3 + ballRadius;
	//����ƶ��ٶ�
	moveX = 10;
	moveY = 10;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			map[i][j] = -1;
		}
	}
	//ʹ����ש�����ɫ���������������5����ɫ
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
	//��ʼ������ߴ�
	hwnd = initgraph(width, high);
	WelcomPage();
	//���û��汳����ɫ
	setbkcolor(RGB(240, 237, 220));
}

//��ש��
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


//չʾ����
void show()
{
	//ˢ�»���
	cleardevice();

	//��ש��ͼ
	drawBrickMap();

	//��ľ��
	setfillcolor(RGB(117, 135, 139));
	solidrectangle(boardX, boardY, boardX + boardWidth, boardY + boardY + boardHigh);

	//��Բ
	setfillcolor(RGB(66, 75, 80));
	solidcircle(ballX, ballY, ballRadius);

	FlushBatchDraw();
	Sleep(40);
}