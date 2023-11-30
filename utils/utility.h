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
#include <wchar.h>
#include <locale.h>


typedef enum ScreenAlign
{
	_ALIGN_NONE_ = -100,
	_ALIGN_CENTER_,

	_ALIGN_LEFT_,
	_ALIGN_RIGHT_,

	_ALIGN_TOP_,
	_ALIGN_BOTTOM_,

} ScreenAlign;

typedef enum InputType
{
	_CARRIGE_RETURN_ = 13,
	_SPACE_ = 32,
	_ESCAPE_ = 27,

	_LEFT_ = 75,
	_RIGHT_ = 77,
	_UP_ = 72,
	_DOWN_ = 80,

	_UPPER_A_ = 65,
	_UPPER_B_,
	_UPPER_C_,
	_UPPER_D_,
	_UPPER_E_,
	_UPPER_F_,
	_UPPER_G_,
	_UPPER_H_,
	_UPPER_I_,
	_UPPER_J_,
	_UPPER_K_,
	_UPPER_L_,
	_UPPER_M_,
	_UPPER_N_,
	_UPPER_O_,
	_UPPER_P_,
	_UPPER_Q_,
	_UPPER_R_,
	_UPPER_S_,
	_UPPER_T_,
	_UPPER_U_,
	_UPPER_V_,
	_UPPER_W_,
	_UPPER_X_,
	_UPPER_Y_,
	_UPPER_Z_,

	_LOWER_A_ = 97,
	_LOWER_B_,
	_LOWER_C_,
	_LOWER_D_,
	_LOWER_E_,
	_LOWER_F_,
	_LOWER_G_,
	_LOWER_H_,
	_LOWER_I_,
	_LOWER_J_,
	_LOWER_K_,
	_LOWER_L_,
	_LOWER_M_,
	_LOWER_N_,
	_LOWER_O_,
	_LOWER_P_,
	_LOWER_Q_,
	_LOWER_R_,
	_LOWER_S_,
	_LOWER_T_,
	_LOWER_U_,
	_LOWER_V_,
	_LOWER_W_,
	_LOWER_X_,
	_LOWER_Y_,
	_LOWER_Z_,

} InputType;

// Open Source Code to Use 'wcwidth()' func
// https://github.com/mattn/wcwidth.c/blob/master/wcwidth.c
struct interval
{
	long first;
	long last;
};


/* utility func of this game */
void gotoxy(int x, int y);
void printString(char* s, int x, int y);
void clearScreen();




/* game initialization func*/
void initGame();
void drawBorder();




/* pure utility func */
void setStringInfo(wchar_t* ws, int* w, int* h);
void fixEachLine(char* beginIdx, short* x);
static int bisearch(wchar_t ucs, const struct interval* table, int max);
int wcwidth(wchar_t ucs);






#endif