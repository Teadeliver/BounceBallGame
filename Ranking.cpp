#include"GAME.h"

//录入本次游戏信息，并写入文件
void ScoreSave()
{
	FILE* fpTemp;
	PLAYER* playerTemp = NULL, * tmp = NULL;
	int inDex = 0, flag = 0;

	//打开文件
	if ((fpTemp = fopen("list.txt", "r+")) == NULL)
	{
		exit(1);
	}

	//读出文件到playerTemp所指向的结构体数组
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
	_stprintf(mestr, _T("你的分数是 %d ,请输入你要录入排行榜的昵称："), player->scoreNow);
	InputBox(player->name, 12, mestr);

	//对比昵称
	for (int i = 0; i < inDex; i++)
	{
		if (strcmp(player->name, playerTemp[i].name) == 0)
		{
			//更新数据
			playerTemp[i].scoreNow = player->scoreNow;
			//最高分数更改
			if (player->scoreNow > playerTemp[i].highScore)
			{
				playerTemp->highScore = player->scoreNow;
			}
			playerTemp[i].time += player->time;//累计游戏时间更改
			playerTemp[i].frequency += player->frequency;//累计游戏次数更改
			flag = 1;//已经修改
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
			playerTemp[inDex].time = player->time;//游戏时间写入
			playerTemp[inDex].frequency = player->frequency;//游戏次数写入
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

//读取排行榜文件内容，存入结构体数组，并排序
void ScoreSort()
{
	FILE* fpTemp;
	PLAYER* playerTemp = NULL, * tmp = NULL;
	PLAYER temp;
	int flag = 0, inDex = 0;

	//打开文件
	if ((fpTemp = fopen("list.txt", "r")) == NULL)
	{
		exit(1);
	}
	//读出文件到playerTemp所指向的结构体数组
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

	//冒泡排序
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

	//写入排名
	for (int i = 0; i < inDex; i++)
	{
		playerTemp[i].ranking = i + 1;
	}

	//打开文件，写入文件
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

//输出排行榜
void ScorePrint(int sign)
{
	int ch;
	FILE* fpTemp;
	PLAYER* playerTemp = NULL, * tmp = NULL;
	int flag = 0, inDex = 0;
	setbkcolor(RGB(56, 142, 142));
	cleardevice();								//刷新背景

	settextstyle(60, 0, "黑体");
	settextcolor(WHITE);
	outtextxy(150, 50, "排行榜");

	if (sign == 0)
	{
		setbkcolor(YELLOW);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, "黑体");
		outtextxy(120, 500, "返回主菜单   F1");
	}

	ScoreSort();
	//打开文件
	if ((fpTemp = fopen("list.txt", "r")) == NULL)
	{
		exit(1);
	}
	//读出文件到playerTemp所指向的结构体数组
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

	setbkcolor(RGB(255, 239, 219));				//设置文字的背景色
	setbkmode(TRANSPARENT);							//文字输出时的背景模式（透明）
	settextcolor(RED);							//设置文字颜色
	//抗锯齿显示文字，效果更好
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 20;						// 设置字体高度为 20
	_tcscpy(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式

	char mestr[100];
	outtextxy(30, 210, _T("名次   昵称   最高分数 游戏总时长 游戏总次数"));			//打印选项

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