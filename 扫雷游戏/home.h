#define  _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"winmm.lib")//播放音乐的静态库文件
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<mmsystem.h>



void menu();
void initialize(char arr[40][40], int h, int l, char mod);
void display(char arr[40][40], int h, int l);
void game();
void Layout(char arr[40][40]);
char num(char arr[40][40], int x, int y);
int outcome(char arr[40][40]);
void coordinate(char mine[40][40], char mail[40][40]);
void level();
void explode(char mail[40][40],char mine[40][40], int a, int b);