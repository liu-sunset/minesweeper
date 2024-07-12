#define  _CRT_SECURE_NO_WARNINGS
#include "home.h"
int row;//���ӵ�������
int col;//���ӵ�������
int rows;//�����ӵ�������
int cols;//�����ӵ�������
int bomb;//���õ�ը��������
int max;//���Ʊ�ըЧ�������������ַ�ը��������
int searchrange;//���Ʊ�ըЧ����Ч�ķ�Χ
int serialnumber;//�������̵ķֲ�
extern  char musics[50][50];//�������ֵ��ַ���
extern char stopmusics[50][50];//ֹͣ���ֵ��ַ���
extern int musicn;//��ǰ���ڲ��ŵ��������
void menu()//�˵���ʾ
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	printf("\t\t\t\t\t\t    *******   1:��ʼ  ********\n");
	printf("\t\t\t\t\t\t    *******   0:�˳�  ********\n");
	printf("\t\t\t\t\t\t    *******  -1:����  ********\n");
	printf("\t\t\t\t\t\t    ***********��ͭ***********\n");
	printf("\t\t\t\t\t\t    ***********�ƽ�***********\n");
	printf("\t\t\t\t\t\t    ***********��ҫ***********\n");
	printf("\t\t\t\t\t\t    ***********����***********\n");
	printf("\t\t******1:ä��**2:ä��**3:ä��**4:��������**5:(һ�׸�����)**6:���䲩���******\n");
}
void initialize(char arr[40][40], int h, int l, char mod)//��ʼ����Ԫ����
{
	int i, j;
	for(i=0;i<h;i++)
		for (j = 0; j < l; j++)
		{
			arr[i][j] = mod;
		}
}


void display(char arr[40][40], int h, int l)//��������
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

void Layout(char arr[40][40])//����ը��
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
char num(char arr[40][40], int x, int y)//ͳ����Χ3*3��Χը��������
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

int outcome(char arr[40][40])//ͳ�����ھ����Ͽ�����ը��������
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
void mark(char mail[40][40],int a,int b)//���ը��
{
	mail[a][b] = '&';
}

void clear_input_buffer() //��ջ�����
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}


void explode(char arr[40][40],char arr2[40][40], int a, int b)//ʵ�ֱ�ը
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


void coordinate(char mine[40][40], char mail[40][40])//���������Լ����
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//��þ��
	int end;//�ж���Ҫ��ը�����Ǳ��ը��
	int come = 0;
	int a, b;//��������
	int c, d;//�������
	
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		come = 0;
			while (1)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				printf("(������x,yͬΪ0ʱ��ʼ�����)����������->");
				scanf("%d%d", &a, &b);
				clear_input_buffer();
				printf("\n\n");
				if (a > row || a <0 || b > col || b <0||(a==0&&b!=0)||(b==0&&a!=0))
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					printf("\t\t\t\t\t\t\t  ���겻�Ϸ���\n\a");
				}
				else if (a == 0 && b == 0)
				{
					printf("������Ҫ��ǵ�����->");
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
						printf("\n\n\t\t\t\t\t\t\t�������Ѿ��Ų���ˣ�������ѡ��\a\n\n");
					}
					else
					{
						if (mine[a][b] == '1')
						{
							mail[a][b] = '@';
							SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
							printf("\n\t\t\t\t\t\t\tgame over!�����ˣ�\n");
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
							if (possibility <= 8)//��8�ɵĸ��ʻᱬը
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

								printf("\t\t\t\t\t\t\t  ��ϲʤ����\n\n\n");
								break;
							}
						}
						
					}
				}
			}
}
void rules()//�����б�
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	printf("\t\t\t          \t\t\t    ��Ϸ����\n\t\t\t\t\t\t     @���׵ı�־ &�����ǵ���");
	printf("\n\t\t\t\t\t    ��Ϸ�������ı����0Ϊ���ף�1�ǲ��õ���\n\t\t\t\t\t\t\t����2���ʱ���Ķ�\n");
}
void level()//�Ѷ�ѡ��
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1)
	{
		char liu[10] = { '\0' };
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		printf("��ѡ�����׳̶�->");
		scanf("%s", liu);
		if (strcmp(liu, "�ƽ�") == 0)
		{
			row = 9; col = 9;
			rows = row + 2; cols = col + 2;
			bomb = 24;
			max = 6;
			searchrange = 1;
			serialnumber = 6;
			break;
		}
		else if (strcmp(liu, "��ҫ") == 0)
		{
			row = 16; col = 16;
			rows = row + 2; cols = col + 2;
			bomb = 45;
			max = 12;
			searchrange = 2;
			serialnumber = 5;
			break;
		}
		else if (strcmp(liu, "����") == 0)
		{
			row = 16; col = 30;
			rows = row + 2; cols = col + 2;
			bomb = 120;
			max = 15;
			searchrange = 3;
			serialnumber = 2;
			break;
		}
		else if (strcmp(liu, "��ͭ") == 0)
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
			printf("\t\t\t  �Ѷ�ѡ�����!\n\n\a");
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