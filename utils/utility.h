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
	_X_CENTER_,
	_X_LEFT_,
	_X_RIGHT_,
	_Y_CENTER_,
	_Y_TOP_,
	_Y_BOTTOM_,
} ScreenAlign;


/* pure utility func */
int convertXPos(int x, int len);
int convertYPos(int y, int height);
int getStringHeight(char *s);


/* utility func of this game */
void initGame();
void drawBorder();
void clearScreen();
void gotoxy(int x, int y);
void printString(char *s, int x, int y);


#endif