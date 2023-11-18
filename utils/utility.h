#ifndef __UTILDATA__
#define __UTILDATA__

#define _SCREEN_WIDTH_		60
#define _SCREEN_HEIGHT_		24

#define _BORDER_LEFT_		0
#define _BORDER_RIGHT_		_SCREEN_WIDTH_+2

#define _BORDER_TOP_		0
#define _BORDER_BOTTOM_		_SCREEN_HEIGHT_+2



#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>


typedef enum ScreenAlign
{
	_ALIGN_NONE_ = -100,
	_ALIGN_CENTER_,

	_ALIGN_LEFT_,
	_ALIGN_RIGHT_,

	_ALIGN_TOP_,
	_ALIGN_BOTTOM_,

} ScreenAlign;






/* utility func of this game */
void gotoxy(int x, int y);
void printString(char* s, int x, int y);
void clearScreen();




/* pure utility func */
void setStringInfo(char* s, int* w, int* h);
void fixEachLine(char* beginIdx, short* x);




/* game initialization func*/
void initGame();
void drawBorder();





#endif