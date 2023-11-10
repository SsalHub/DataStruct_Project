#include "UtilData.h"

void gotoxy(int x, int y)
{
    printf("\033[%d;%df",y,x);
	fflush(stdout);
}

void waitForSeconds(float s)
{
    #ifdef _WIN32 || _WIN64
    Sleep(s * 1000);    // windows.h
    #else
    sleep(s);           // unistd.h
    #endif
}