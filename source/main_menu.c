#define _CRT_SECURE_NO_WARNINGS
#include "main_menu.h"

void showMainMenu()
{
    clearScreen();
    char buffer[64];
    int x, y, len;

    strcpy(buffer, "Main Menu");
    printString(buffer, _ALIGN_CENTER_, _ALIGN_CENTER_);

    strcpy(buffer, "Press Any Key.");
    printString(buffer, _ALIGN_CENTER_, _ALIGN_BOTTOM_);
    while (!_kbhit());

}
