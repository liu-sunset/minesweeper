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
		printf("\t\t\t\t\t��ѡ��ʹ�ð汾->(1.����汾��2.����汾)");
		scanf("%s", version);
		if (strcmp(version, "����汾") == 0)
		{
			HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			// �������̨������Ϣ�ṹ��
			CONSOLE_FONT_INFOEX font;
			font.cbSize = sizeof(font);

			// ��ȡ��ǰ����̨������Ϣ
			GetCurrentConsoleFontEx(consoleHandle, FALSE, &font);

			// ���������СΪ20
			font.dwFontSize.X = 25;
			font.dwFontSize.Y = 25;

			// Ӧ���µ�������Ϣ
			SetCurrentConsoleFontEx(consoleHandle, FALSE, &font);
			break;
		}
		else if (strcmp(version, "����汾") == 0)
		{
			HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			// �������̨������Ϣ�ṹ��
			CONSOLE_FONT_INFOEX font;
			font.cbSize = sizeof(font);

			// ��ȡ��ǰ����̨������Ϣ
			GetCurrentConsoleFontEx(consoleHandle, FALSE, &font);

			// ���������СΪ20
			font.dwFontSize.X = 20;
			font.dwFontSize.Y = 20;

			// Ӧ���µ�������Ϣ
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
		printf("��ѡ��->");
		
		scanf("%d", &input);
		if (input == 1)
		{
			while (1)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				printf("\n��ѡ�񱳾�����->");
				if (musicn != 0)
					mciSendStringA(stopmusics[musicn - 1], 0, 0, 0);
				scanf("%d", &musicn);
				if (!(musicn >= 1 && musicn <= 6))
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					printf("\t\t\t  ��������ѡ�����\a\n");
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
			printf("\t\t������3����˳�����ӭ�´����棡\n");
			Sleep(3000);
		}
			break;
		case -1:
			system("cls");
			break;
		default:
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\t\t�������������ѡ��\n");
		}
			
		}
	} while (input);
	return 0;
}