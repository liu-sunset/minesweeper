#define  _CRT_SECURE_NO_WARNINGS
#include "home.h"
char musics[50][50] = { '\0' };
char stopmusics[50][50] = { '\0' };
int musicn;
int main()
{
	
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
		printf("ÇëÑ¡Ôñ->");
		
		scanf("%d", &input);
		if (input == 1)
		{
			while (1)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				printf("\nÇëÑ¡Ôñ±³¾°ÒôÀÖ->");
				if (musicn != 0)
					mciSendStringA(stopmusics[musicn - 1], 0, 0, 0);
				scanf("%d", &musicn);
				if (!(musicn >= 1 && musicn <= 6))
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					printf("\t\t\t  ±³¾°ÒôÀÖÑ¡Ôñ´íÎó£¡\a\n");
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
			printf("\t\t¼´½«ÔÚ3ÃëºóÍË³ö£¬»¶Ó­ÏÂ´ÎÀ´Íæ£¡\n");
			Sleep(3000);
		}
			break;
		case -1:
			system("cls");
			break;
		default:
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\t\tÊäÈë´íÎó£¡ÇëÖØÐÂÑ¡Ôñ£¡\n");
		}
			
		}
	} while (input);
	return 0;
}