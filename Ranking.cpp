#include"GAME.h"

//¼�뱾����Ϸ��Ϣ����д���ļ�
void ScoreSave()
{
	FILE* fpTemp;
	PLAYER* playerTemp = NULL, * tmp = NULL;
	int inDex = 0, flag = 0;

	//���ļ�
	if ((fpTemp = fopen("list.txt", "r+")) == NULL)
	{
		exit(1);
	}

	//�����ļ���playerTemp��ָ��Ľṹ������
	playerTemp = (PLAYER*)malloc(sizeof(PLAYER));
	if (playerTemp && fscanf(fpTemp, "%s %d %d %d %d %d", playerTemp[inDex].name,
		&playerTemp[inDex].scoreNow, &playerTemp[inDex].frequency, 
		&playerTemp[inDex].ranking, &playerTemp[inDex].highScore,
		& playerTemp[inDex].time) == 6)
		inDex++;
	while (!feof(fpTemp))
	{
		tmp = (PLAYER*)realloc(playerTemp, ((inDex + 1) * sizeof(PLAYER)));
		playerTemp = tmp;
		if (playerTemp && fscanf(fpTemp, "%s %d %d %d %d %d", playerTemp[inDex].name,
			&playerTemp[inDex].scoreNow, &playerTemp[inDex].frequency,
			&playerTemp[inDex].ranking, &playerTemp[inDex].highScore,
			&playerTemp[inDex].time) == 6)
			inDex++;
	}
	fclose(fpTemp);

	char mestr[50];
	_stprintf(mestr, _T("��ķ����� %d ,��������Ҫ¼�����а���ǳƣ�"), player->scoreNow);
	InputBox(player->name, 12, mestr);

	//�Ա��ǳ�
	for (int i = 0; i < inDex; i++)
	{
		if (strcmp(player->name, playerTemp[i].name) == 0)
		{
			//��������
			playerTemp[i].scoreNow = player->scoreNow;
			//��߷�������
			if (player->scoreNow > playerTemp[i].highScore)
			{
				playerTemp->highScore = player->scoreNow;
			}
			playerTemp[i].time += player->time;//�ۼ���Ϸʱ�����
			playerTemp[i].frequency += player->frequency;//�ۼ���Ϸ��������
			flag = 1;//�Ѿ��޸�
			break;
		}
	}
	if (flag == 0)
	{
		tmp = (PLAYER*)realloc(playerTemp, ((inDex + 1) * sizeof(PLAYER)));
		playerTemp = tmp;

		if (playerTemp)
		{
			playerTemp[inDex].highScore = player->scoreNow;
			playerTemp[inDex].scoreNow = player->scoreNow;
			playerTemp[inDex].ranking = 0;
			playerTemp[inDex].time = player->time;//��Ϸʱ��д��
			playerTemp[inDex].frequency = player->frequency;//��Ϸ����д��
		}
		inDex++;
	}
	
	if ((fpTemp = fopen("list.txt", "w")) == NULL)
	{
		exit(1);
	}
	for ( int i = 0; i < inDex; i++)
	{
		if (i == inDex - 1 && flag == 0)
		{
			if(playerTemp)
			fprintf(fpTemp, "%s %d %d %d %d %d\n", player->name,
				playerTemp[i].scoreNow, playerTemp[i].frequency, playerTemp[i].ranking,
				playerTemp[i].highScore, playerTemp[i].time);
		}
		else
		{
			fprintf(fpTemp, "%s %d %d %d %d %d\n", playerTemp[i].name,
				playerTemp[i].scoreNow, playerTemp[i].frequency, playerTemp[i].ranking,
				playerTemp[i].highScore, playerTemp[i].time);
		}
	}
	fclose(fpTemp);
	ScoreSort();
}

//��ȡ���а��ļ����ݣ�����ṹ�����飬������
void ScoreSort()
{
	FILE* fpTemp;
	PLAYER* playerTemp = NULL, * tmp = NULL;
	PLAYER temp;
	int flag = 0, inDex = 0;

	//���ļ�
	if ((fpTemp = fopen("list.txt", "r")) == NULL)
	{
		exit(1);
	}
	//�����ļ���playerTemp��ָ��Ľṹ������
	playerTemp = (PLAYER*)malloc(sizeof(PLAYER));
	if (playerTemp && fscanf(fpTemp, "%s %d %d %d %d %d", playerTemp[inDex].name,
		&playerTemp[inDex].scoreNow, &playerTemp[inDex].frequency,
		&playerTemp[inDex].ranking, &playerTemp[inDex].highScore,
		&playerTemp[inDex].time) == 6)
		inDex++;
	while (!feof(fpTemp))
	{
		tmp = (PLAYER*)realloc(playerTemp, ((inDex + 1) * sizeof(PLAYER)));
		playerTemp = tmp;
		if (playerTemp && fscanf(fpTemp, "%s %d %d %d %d %d", playerTemp[inDex].name,
			&playerTemp[inDex].scoreNow, &playerTemp[inDex].frequency,
			&playerTemp[inDex].ranking, &playerTemp[inDex].highScore,
			&playerTemp[inDex].time) == 6)
			inDex++;
	}
	fclose(fpTemp);

	//ð������
	for (int i = 0; i < inDex; i++)
	{
		for (int j = 0; j < inDex - 1 - i; j++)
		{
			if (playerTemp[j].highScore < playerTemp[j + 1].highScore)
			{
				temp = playerTemp[j];
				playerTemp[j] = playerTemp[j + 1];
				playerTemp[j + 1] = temp;
			}
		}
	}

	//д������
	for (int i = 0; i < inDex; i++)
	{
		playerTemp[i].ranking = i + 1;
	}

	//���ļ���д���ļ�
	if ((fpTemp = fopen("list.txt", "w")) == NULL)
	{
		exit(1);
	}
	for (int i = 0; i < inDex; i++)
	{
		fprintf(fpTemp, "%s %d %d %d %d %d\n", playerTemp[i].name,
			playerTemp[i].scoreNow, playerTemp[i].frequency,
			playerTemp[i].ranking, playerTemp[i].highScore,
			playerTemp[i].time);
	}
	fclose(fpTemp);
}

//������а�
void ScorePrint(int sign)
{
	int ch;
	FILE* fpTemp;
	PLAYER* playerTemp = NULL, * tmp = NULL;
	int flag = 0, inDex = 0;
	setbkcolor(RGB(56, 142, 142));
	cleardevice();								//ˢ�±���

	settextstyle(60, 0, "����");
	settextcolor(WHITE);
	outtextxy(150, 50, "���а�");

	if (sign == 0)
	{
		setbkcolor(YELLOW);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, "����");
		outtextxy(120, 500, "�������˵�   F1");
	}

	ScoreSort();
	//���ļ�
	if ((fpTemp = fopen("list.txt", "r")) == NULL)
	{
		exit(1);
	}
	//�����ļ���playerTemp��ָ��Ľṹ������
	playerTemp = (PLAYER*)malloc(sizeof(PLAYER));
	if (playerTemp && fscanf(fpTemp, "%s %d %d %d %d %d", playerTemp[inDex].name,
		&playerTemp[inDex].scoreNow, &playerTemp[inDex].frequency,
		&playerTemp[inDex].ranking, &playerTemp[inDex].highScore,
		&playerTemp[inDex].time) == 6)
		inDex++;
	while (!feof(fpTemp))
	{
		tmp = (PLAYER*)realloc(playerTemp, ((inDex + 1) * sizeof(PLAYER)));
		playerTemp = tmp;
		if (playerTemp && fscanf(fpTemp, "%s %d %d %d %d %d", playerTemp[inDex].name,
			&playerTemp[inDex].scoreNow, &playerTemp[inDex].frequency,
			&playerTemp[inDex].ranking, &playerTemp[inDex].highScore,
			&playerTemp[inDex].time) == 6)
			inDex++;
	}
	fclose(fpTemp);

	setbkcolor(RGB(255, 239, 219));				//�������ֵı���ɫ
	setbkmode(TRANSPARENT);							//�������ʱ�ı���ģʽ��͸����
	settextcolor(RED);							//����������ɫ
	//�������ʾ���֣�Ч������
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 20
	_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ

	char mestr[100];
	outtextxy(30, 210, _T("����   �ǳ�   ��߷��� ��Ϸ��ʱ�� ��Ϸ�ܴ���"));			//��ӡѡ��

	int number = 5;
	if (inDex < 5)
	{
		number = inDex;
	}
	for (int i = 0; i < number; i++)
	{
		sprintf(mestr, "%2d%10s%7d%9ds%11d",
			playerTemp[i].ranking, playerTemp[i].name,
			playerTemp[i].highScore, playerTemp[i].time, playerTemp[i].frequency);
		outtextxy(30, 260 + 50 * i, mestr);
	}

	if (sign == 0)
	{
		while ((ch = _getch()) != 59)
		{
			continue;
		}
	}
}