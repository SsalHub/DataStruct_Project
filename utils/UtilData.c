#define _CRT_SECURE_NO_WARNINGS
#include "UtilData.h"

void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(stdout, pos); 
}