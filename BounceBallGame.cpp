#include"GAME.h"

int map[19][7] = {-1};//ש��ĵ�ͼ
int ballX, ballY;//��Բ�ĵ�����
int ballRadius;//��뾶
int boardX, boardY;//�����Ͻǵ�����
int boardWidth, boardHigh;//��Ŀ�͸�
int brickWidth, brickHigh;//ש��Ŀ�͸�
int width, high;//����Ŀ�͸�
int moveX, moveY;//����ƶ��ٶ�
int come = 0;
HWND hwnd;
FILE* fp = NULL;
PLAYER* player = NULL;
time_t start, end;
int main()
{
	char ch;
	int flag = 0;					//������Ϸ�ı�־
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
					updateShow();//����ש������
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
			HelpPage();				//����ҳ��
			WelcomPage();
			break;
		}
		case 62:					//F4
		{
			AboutPage();			//����ҳ��
			WelcomPage();
			break;
		}
		case 63:					//F5
			exit(EXIT_SUCCESS);		//�˳�
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
