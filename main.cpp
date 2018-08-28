#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

int map[24][13] = { 0 };
int score = 0;

int x, y;
int i, j;
int p, q;
int flag; 

char c;

TCHAR s[50];

enum  block {
	Sauqre,
	Rectangle,
	Lefts,
	Rights,
	Leftz,
	Rightz
} Block;

Create sq();


void Create(int m)
{

	for (i = 0; i < 24; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (map[i][j] == 1)
			{
				setfillcolor(BLUE);
			//	map[y / 2][(x - 15) / 2] = 1;
				solidrectangle((j*2+15) * 10, i*2* 10, (j*2+2+15) * 10, (i+ 2)* 2 * 10);
			}
		}
	}
}
void Check(int m)
{
	for (j = 0; j < 13; j++)
	{
		for (i = 0; i < m; i++)
		{
			if (map[i][j] == 1)
			{
				map[i][j] = 0;
				map[m][j] = 1;
				break;
			}
		}
	}
}
void init()
{


	initgraph(640, 480);
	srand((unsigned)time(NULL));
	setbkmode(TRANSPARENT);			// 设置图案填充的背景色为透明
	rectangle(150, 0, 410, 480);//25

	settextstyle(14, 0, _T("宋体"));
	outtextxy(20, 330, _T("操作说明"));
	outtextxy(20, 350, _T("上：旋转"));
	outtextxy(20, 370, _T("左：左移"));
	outtextxy(20, 390, _T("右：右移"));
	outtextxy(20, 410, _T("下：下移"));
	outtextxy(20, 430, _T("空格：沉底"));
	outtextxy(20, 450, _T("ESC：退出"));
	outtextxy(20, 450, _T("ESC：退出"));



}
void flushscore()
{
	settextcolor(BLACK);
	_stprintf_s(s, _T("积分:%d"), score);
	outtextxy(20, 100, s);
}
void showscore()
{
	settextcolor(WHITE);
	_stprintf_s(s, _T("积分:%d"), score);
	outtextxy(20, 100, s);
}
void counts()
{
	clearrectangle(150, y * 10, 410, (y + 2) * 10);
	flushscore();
	score++;
	showscore();
	memset(map, 0, sizeof(map));
}
int Gameover()
{
	for (j = 0; j < 13; j++)
	{
		for (i = 0; i < 24; i++)
		{
			if (map[i][j] != 1)
				break;
		}
		if (i == 24)
		{
			clearrectangle(150, 0, 410, 480);
			rectangle(150, 0, 410, 480);
			settextstyle(14, 0, _T("宋体"));
			outtextxy(250, 240, _T("游戏结束"));
			getchar();
			getchar();
			exit(1);
		}
	}

}
void Judge()
{
	int flag = 0;
	for (i = 0; i < 24; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (map[i][j] == 0)break;
		}
		if (j == 13)
		{
			clearrectangle(150,0, 410, 480);
			flushscore();
			score++;
			showscore();
			memset(map[i],0,sizeof(int)*13);
			Check(i);
			Create(i);
			break;
		}
	}
}


void main()
{
	init();
	showscore();

	
a:
	x = 15 + rand() % 25;
	while(x % 2 == 0)
	x = 15 + rand() % 25;
	y = 0;
	setfillcolor(BLUE);
	solidrectangle(x * 10,y * 10 ,(x+2) * 10, (y +2)*10);


	while (1)
	{
		if (_kbhit())
			c = _getch();
		else
			c = 's';

		setfillcolor(BLACK);
		solidrectangle(x * 10, y * 10, (x + 2) * 10, (y + 2) * 10);

		for (p = 0; p < 48; p= p+2)
		{
			setlinecolor(RGB(66,66,66));
			setlinestyle(PS_DASHDOT);
			line(150, p * 10, 410, p * 10);
		}
		for (p = 2; p < 26; p = p + 2)
		{
			setlinecolor(RGB(66, 66, 66));
			setlinestyle(PS_DASHDOT);
			line((15 + p) * 10, 0, (15 + p) * 10, 480);
		}

		setlinestyle(PS_SOLID);
		setlinecolor(WHITE);
		rectangle(150, 0, 410, 480);//25
	
		switch (c) 
		{
			case 'a': 
				if (x <= 15)
				{
					x = 15;
					break;
				}
				else if (1 == map[y / 2][(x - 15 -2 ) / 2])
				{
					break;
				}
				x =x - 2;
				setfillcolor(BLUE);
				solidrectangle(x * 10, y * 10, (x + 2) * 10, (y + 2) * 10);
				break;
			default:
			case 's': 
				if (map[(y + 2) / 2][(x - 15) / 2] == 1 )
				{
					map[y / 2][(x - 15) / 2] = 1;
					setfillcolor(BLUE);
					solidrectangle(x * 10, y * 10, (x + 2) * 10, (y+2) * 10);
					Judge();
					goto a;
				}
				else
				{
					y = y + 2;
					if (y > 46)
					{
						map[23][(x - 15) / 2] = 1;
						setfillcolor(BLUE);
						solidrectangle(x * 10, (y-2) * 10, (x + 2) * 10, y  * 10);
						Gameover();
						Judge();
						goto a;
					}
				}
				break;
			case 'd':if (x >= 39)
					{
						x = 39;
						break;
					}
					 else if (1 == map[y / 2][(x - 15 + 2) / 2])
					 {
						 break;
					 }
					 x = x + 2;
					 setfillcolor(BLUE);
					 solidrectangle(x * 10, y * 10, (x + 2) * 10, (y + 2) * 10);
					 break;
		}

		setfillcolor(BLUE);
		solidrectangle(x * 10, y * 10, (x + 2) * 10, (y + 2) * 10);
		Sleep(80);

	}

	getchar();
	closegraph();
}

