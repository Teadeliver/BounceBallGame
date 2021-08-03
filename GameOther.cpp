#include"GAME.h"

//帮助页面
void HelpPage()
{
	int ch;

	setbkcolor(RGB(56, 142, 142));
	cleardevice();								//刷新背景

	settextstyle(50, 0, "黑体");
	settextcolor(WHITE);					//设置字体颜色
	outtextxy(180, 40, "帮助");

	settextcolor(BLACK);							//设置字体颜色  红色
		//抗锯齿显示文字，效果更好
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 20;						// 设置字体高度为 20
	_tcscpy(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	//打印帮助文档
	outtextxy(120, 240, "使用方向键← 或者 → 移动木板");
	outtextxy(120, 270, "使用方向键A 或者 D 移动木板");
	outtextxy(120, 300, "别让小球坠入木板以下的区域");
	outtextxy(120, 330, "别让砖块进入木板以下的区域");
	outtextxy(120, 360, "否则游戏将会结束");
	outtextxy(120, 390, "尽一切可能坚持下去！！！！");

	setfillcolor(RGB(255, 239, 219));

	setbkcolor(YELLOW);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "黑体");
	outtextxy(130, 500, "返回主菜单   F1");


	while ((ch = _getch()) != 59)
	{
		continue;
	}
}

//关于页面
void AboutPage()
{
	int ch;

	setbkcolor(RGB(56, 142, 142));
	cleardevice();								//刷新背景

	settextstyle(50, 0, "黑体");
	settextcolor(WHITE);					//设置字体颜色
	outtextxy(180, 40, "关于");

	settextcolor(BLACK);
	settextstyle(20, 0, "斜体");			//帮助文档
	outtextxy(120, 200, "版本: V1.0");
	outtextxy(120, 230, "版本号: 001(简易)");
	outtextxy(120, 260, "制作人: 吴浩斌");
	outtextxy(120, 290, "如果您在游戏体验中发现某些BUG");
	outtextxy(120, 310, "请您给我们发邮件:");
	outtextxy(120, 340, "192354134@qq.com");
	outtextxy(120, 370, "祝您游戏愉快！");

	setfillcolor(YELLOW);
	setbkcolor(YELLOW);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "黑体");
	outtextxy(130, 500, "返回主菜单   F1");

	while ((ch = _getch()) != 59)
	{
		continue;
	}
}