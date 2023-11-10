#ifndef __UTILDATA__
#define __UTILDATA__

#include <stdio.h>
#ifdef _WIN32 || _WIN64
#include <windows.h>
#else
#include <unistd.h>
#endif

void gotoxy(int x, int y);
void waitForSeconds(float s);

#endif