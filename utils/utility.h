#ifndef __UTILDATA__
#define __UTILDATA__

#define _SCREEN_WIDTH_	60
#define _SCREEN_HEIGHT_	24

#define _CENTER_	0
#define _LEFT_		1
#define _RIGHT_		2
#define _UP_		3
#define _DOWN_		4


#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

void initGame();
void drawBorder();
void gotoxy(int x, int y);

#endif