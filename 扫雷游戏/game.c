#define  _CRT_SECURE_NO_WARNINGS
#include "home.h"
int row;//可视的行数量
int col;//可视的列数量
int rows;//不可视的行数量
int cols;//不可视的列数量
int bomb;//布置的炸弹的数量
int max;//控制爆炸效果产生后最大出现非炸弹的数量
int searchrange;//控制爆炸效果生效的范围
int serialnumber;//控制棋盘的分布
extern  char musics[50][50];//播放音乐的字符串
extern char stopmusics[50][50];//停止音乐的字符串
extern int musicn;//当前正在播放的音乐序号
void menu()//菜单提示
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	printf("\t\t\t\t\t\t    *******   1:开始  ********\n");
	printf("\t\t\t\t\t\t    *******   0:退出  ********\n");
	printf("\t\t\t\t\t\t    *******  -1:清屏  ********\n");
	printf("\t\t\t\t\t\t    ***********青铜***********\n");
	printf("\t\t\t\t\t\t    ***********黄金***********\n");
	printf("\t\t\t\t\t\t    ***********星耀***********\n");
	printf("\t\t\t\t\t\t    ***********王者***********\n");
	printf("\t\t******1:盲盒**2:盲盒**3:盲盒**4:向阳生长**5:(一首钢琴曲)**6:记忆博物馆******\n");
}
void initialize(char arr[40][40], int h, int l, char mod)//初始化二元数组
{
	int i, j;
	for(i=0;i<h;i++)
		for (j = 0; j < l; j++)
		{
			arr[i][j] = mod;
		}
}


void display(char arr[40][40], int h, int l)//陈列数组
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	printf("\t--------------------------------------------------------display------------------------------------------------\n");
	int i, j, m;
	printf("   ");
	for (i = 0; i < serialnumber; i++)
		printf("\t");
	printf("   ");
	for (i = 1; i <= l; i++)
	{
		printf("%d", i);
		if (i < 10)
			printf("  ");
		else
			printf(" ");
	}
	printf("\n\n");
	for (i = 1; i <= h; i++)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		for (m = 0; m < serialnumber; m++)
			printf("\t");
		printf("%d", i);
		if (i < 10)
			printf("  ");
		else
			printf(" ");
		for (j = 1; j <= l; j++)
		{
			if (arr[i][j] != '*')
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				printf("%c  ", arr[i][j]);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				printf("%c  ", arr[i][j]);
			}

		}
		printf("\n");
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	printf("\t--------------------------------------------------------display------------------------------------------------\n");
}

void Layout(char arr[40][40])//布置炸弹
{
	int count = bomb;
	while(count)
	{
	int x = rand() % row + 1;
	int y = rand() % col + 1;
	
		if (arr[x][y] == '0')
		{
			arr[x][y] = '1';
			count--;
		}
	}
}
char num(char arr[40][40], int x, int y)//统计周围3*3范围炸弹的数量
{
	int n = 48;
	int i, j;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (arr[x + i][y + j] == '1')
				n++;
		}
			
	}
	return n;
	
}

int outcome(char arr[40][40])//统计现在局面上可能是炸弹的数量
{
	int n = 0;
	int i, j;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
		{
			if (arr[i][j] =='*'||arr[i][j]=='&')
				n++;
		}
	return n;
}
void mark(char mail[40][40],int a,int b)//标记炸弹
{
	mail[a][b] = '&';
}

void clear_input_buffer() //清空缓存区
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}


void explode(char arr[40][40],char arr2[40][40], int a, int b)//实现爆炸
{
	int bombcount = rand() % max + 3;
	int timebombcount = 0;
	for (int i = -2-searchrange; i <=2+searchrange ;i++)
	{
		if (a + i<1 || a + i>row)
			continue;
		for (int j = -2-searchrange; j <= 2+searchrange; j++)
		{
			if (b + j<1 || b + j>col)
				continue;
			if (i == 0 && j == 0)
				continue;
			else 
			{
				if (arr[a + i][b + j] == '*' && arr2[a + i][b + j] == '0')
				{
					int odds = rand() % 10 + 1;
					if(odds<=6)
					arr[a + i][b + j] = num(arr2, a + i, b + j);
				}
					
				timebombcount++;
				if (timebombcount == bombcount)
					break;
			}
		}
		if (timebombcount == bombcount)
			break;
	}
}


void coordinate(char mine[40][40], char mail[40][40])//坐标输入以及检测
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//获得句柄
	int end;//判断是要找炸弹还是标记炸弹
	int come = 0;
	int a, b;//拆雷坐标
	int c, d;//标记坐标
	
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		come = 0;
			while (1)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				printf("(当坐标x,y同为0时开始标记雷)请输入坐标->");
				scanf("%d%d", &a, &b);
				clear_input_buffer();
				printf("\n\n");
				if (a > row || a <0 || b > col || b <0||(a==0&&b!=0)||(b==0&&a!=0))
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					printf("\t\t\t\t\t\t\t  坐标不合法！\n\a");
				}
				else if (a == 0 && b == 0)
				{
					printf("请输入要标记的坐标->");
					scanf("%d%d", &c, &d);
					clear_input_buffer();
					mark(mail, c, d);
					display(mail, row, col);
				}
				else
				{
					if (mail[a][b] != '*'&&mail[a][b]!='&')
					{
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						printf("\n\n\t\t\t\t\t\t\t该坐标已经排查过了！请重新选择！\a\n\n");
					}
					else
					{
						if (mine[a][b] == '1')
						{
							mail[a][b] = '@';
							SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
							printf("\n\t\t\t\t\t\t\tgame over!踩雷了！\n");
							display(mail, row, col);
							printf("\n\n");
							display(mine, row, col);
							break;
						}
						else
						{
							char time = num(mine, a, b);
							mail[a][b] = time;
							int possibility;
							possibility = rand() % 10 + 1;
							if (possibility <= 8)//有8成的概率会爆炸
							{
								explode(mail, mine, a, b);
							}
							display(mail, row, col);
							come = outcome(mail);
							if (come == bomb)
							{
								display(mine, row, col);
								float x, y, a;
								mciSendStringA(stopmusics[musicn - 1], 0, 0, 0);
								mciSendStringA("play vectory.mp3 wait", 0, 0, 0);
								for (y = 1.5f; y > -1; y -= 0.1f)
								{
									printf("\t\t\t\t");
									for (x = -1.5f; x < 1.5f; x += 0.05f)
									{
										a = x * x + y * y - 1;
										if (a * a * a - x * x * y * y * y < 0.0f)
										{
											SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
											printf("*");
										}

										else
											printf(" ");
									}
									Sleep(100);
									printf("\n");
								}

								printf("\t\t\t\t\t\t\t  恭喜胜利！\n\n\n");
								break;
							}
						}
						
					}
				}
			}
}
void rules()//规则列表
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	printf("\t\t\t          \t\t\t    游戏规则\n\t\t\t\t\t\t     @是雷的标志 &是你标记的雷");
	printf("\n\t\t\t\t\t    游戏结束最后的表格中0为非雷，1是布置的雷\n\t\t\t\t\t\t\t你有2秒的时间阅读\n");
}
void level()//难度选择
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1)
	{
		char liu[10] = { '\0' };
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		printf("请选择难易程度->");
		scanf("%s", liu);
		if (strcmp(liu, "黄金") == 0)
		{
			row = 9; col = 9;
			rows = row + 2; cols = col + 2;
			bomb = 24;
			max = 6;
			searchrange = 1;
			serialnumber = 6;
			break;
		}
		else if (strcmp(liu, "星耀") == 0)
		{
			row = 16; col = 16;
			rows = row + 2; cols = col + 2;
			bomb = 45;
			max = 12;
			searchrange = 2;
			serialnumber = 5;
			break;
		}
		else if (strcmp(liu, "王者") == 0)
		{
			row = 16; col = 30;
			rows = row + 2; cols = col + 2;
			bomb = 120;
			max = 15;
			searchrange = 3;
			serialnumber = 2;
			break;
		}
		else if (strcmp(liu, "青铜") == 0)
		{
			row = 5; col = 5;
			rows = row + 2; cols = col + 2;
			bomb = 8;
			max = 10;
			searchrange = 0;
			serialnumber = 7;
			break;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\t\t\t  难度选择错误!\n\n\a");
		}
	}
	
}


void game()
{
	mciSendStringA(musics[musicn-1], 0, 0, 0);
	rules();
	Sleep(2000);
	level();
	char mine[40][40] = { '0' };
	char mail[40][40] = { '*' };
	initialize(mine, rows, cols, '0');
	initialize(mail, rows, cols, '*');
	display(mail, row, col);
	Layout(mine);
	coordinate(mine,mail);
}