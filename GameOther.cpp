#include"GAME.h"

//����ҳ��
void HelpPage()
{
	int ch;

	setbkcolor(RGB(56, 142, 142));
	cleardevice();								//ˢ�±���

	settextstyle(50, 0, "����");
	settextcolor(WHITE);					//����������ɫ
	outtextxy(180, 40, "����");

	settextcolor(BLACK);							//����������ɫ  ��ɫ
		//�������ʾ���֣�Ч������
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 20
	_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	//��ӡ�����ĵ�
	outtextxy(120, 240, "ʹ�÷������ ���� �� �ƶ�ľ��");
	outtextxy(120, 270, "ʹ�÷����A ���� D �ƶ�ľ��");
	outtextxy(120, 300, "����С��׹��ľ�����µ�����");
	outtextxy(120, 330, "����ש�����ľ�����µ�����");
	outtextxy(120, 360, "������Ϸ�������");
	outtextxy(120, 390, "��һ�п��ܼ����ȥ��������");

	setfillcolor(RGB(255, 239, 219));

	setbkcolor(YELLOW);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "����");
	outtextxy(130, 500, "�������˵�   F1");


	while ((ch = _getch()) != 59)
	{
		continue;
	}
}

//����ҳ��
void AboutPage()
{
	int ch;

	setbkcolor(RGB(56, 142, 142));
	cleardevice();								//ˢ�±���

	settextstyle(50, 0, "����");
	settextcolor(WHITE);					//����������ɫ
	outtextxy(180, 40, "����");

	settextcolor(BLACK);
	settextstyle(20, 0, "б��");			//�����ĵ�
	outtextxy(120, 200, "�汾: V1.0");
	outtextxy(120, 230, "�汾��: 001(����)");
	outtextxy(120, 260, "������: ��Ʊ�");
	outtextxy(120, 290, "���������Ϸ�����з���ĳЩBUG");
	outtextxy(120, 310, "���������Ƿ��ʼ�:");
	outtextxy(120, 340, "192354134@qq.com");
	outtextxy(120, 370, "ף����Ϸ��죡");

	setfillcolor(YELLOW);
	setbkcolor(YELLOW);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "����");
	outtextxy(130, 500, "�������˵�   F1");

	while ((ch = _getch()) != 59)
	{
		continue;
	}
}