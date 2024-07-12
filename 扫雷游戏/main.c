#define  _CRT_SECURE_NO_WARNINGS
#include "home.h"
char musics[50][50] = { '\0' };
char stopmusics[50][50] = { '\0' };
int musicn;
int main()
{
	
	char version[10];
	do
	{
		printf("\t\t\t\t\t请选择使用版本->(1.青年版本，2.老年版本)");
		scanf("%s", version);
		if (strcmp(version, "老年版本") == 0)
		{
			HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			// 定义控制台字体信息结构体
			CONSOLE_FONT_INFOEX font;
			font.cbSize = sizeof(font);

			// 获取当前控制台字体信息
			GetCurrentConsoleFontEx(consoleHandle, FALSE, &font);

			// 设置字体大小为20
			font.dwFontSize.X = 25;
			font.dwFontSize.Y = 25;

			// 应用新的字体信息
			SetCurrentConsoleFontEx(consoleHandle, FALSE, &font);
			break;
		}
		else if (strcmp(version, "青年版本") == 0)
		{
			HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			// 定义控制台字体信息结构体
			CONSOLE_FONT_INFOEX font;
			font.cbSize = sizeof(font);

			// 获取当前控制台字体信息
			GetCurrentConsoleFontEx(consoleHandle, FALSE, &font);

			// 设置字体大小为20
			font.dwFontSize.X = 20;
			font.dwFontSize.Y = 20;

			// 应用新的字体信息
			SetCurrentConsoleFontEx(consoleHandle, FALSE, &font);
			break;
		}
	}while (1);
	
	for (int i = 0; i < 6; i++)
	{
		sprintf(musics[i], "play back%d.mp3 repeat", i + 1);
		sprintf(stopmusics[i], "stop back%d.mp3", i + 1);
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		printf("请选择->");
		
		scanf("%d", &input);
		if (input == 1)
		{
			while (1)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				printf("\n请选择背景音乐->");
				if (musicn != 0)
					mciSendStringA(stopmusics[musicn - 1], 0, 0, 0);
				scanf("%d", &musicn);
				if (!(musicn >= 1 && musicn <= 6))
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					printf("\t\t\t  背景音乐选择错误！\a\n");
				}
				else
					break;
			}
			
		}
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\t\t即将在3秒后退出，欢迎下次来玩！\n");
			Sleep(3000);
		}
			break;
		case -1:
			system("cls");
			break;
		default:
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\t\t输入错误！请重新选择！\n");
		}
			
		}
	} while (input);
	return 0;
}