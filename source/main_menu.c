#define _CRT_SECURE_NO_WARNINGS
#include "main_menu.h"

void showMainMenu()
{
    char buffer[64];
    int x, y, len;

    strcpy(buffer, "Main Menu");
    printString(buffer, _X_CENTER_, _Y_CENTER_);

    strcpy(buffer, "Press Any Key.");
    printString(buffer, _X_CENTER_, _Y_BOTTOM_);
    while (!_kbhit());

}
