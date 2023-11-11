#include "UtilData.h"

void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(stdout, pos); 
}