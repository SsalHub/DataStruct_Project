#ifndef __UTILDATA__
#define __UTILDATA__

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

void gotoxy(int x, int y);
void waitForSeconds(float s);
int onKeyboardInput();	// kbhit()
char getChar();			// getch()

#endif