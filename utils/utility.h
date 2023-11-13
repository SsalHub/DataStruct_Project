#ifndef __UTILDATA__
#define __UTILDATA__

#define _SCREEN_WIDTH_	60
#define _SCREEN_HEIGHT_	24

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef enum ScreenAlign
{
	_ALIGN_NONE_ = -100,
	_ALIGN_CENTER_,
	_ALIGN_LEFT_,
	_ALIGN_RIGHT_,
	_ALIGN_TOP_,
	_ALIGN_BOTTOM_,
} ScreenAlign;

/* pure utility func */
void gotoxy(int x, int y);
void gotoxyDetailed(int x, int y, int len);


/* utility func of this game */
void initGame();
void drawBorder();
void clearScreen();


#endif