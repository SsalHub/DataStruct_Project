#define _CRT_SECURE_NO_WARNINGS
#include "main_menu.h"

void showMainMenu()
{
    char buffer[64];
    int x, y, len;

    strcpy(buffer, "Main Menu");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, _ALIGN_CENTER_, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "Press Any Key.");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, _ALIGN_BOTTOM_, len);
    fprintf(stdout, "%s\n", buffer);
    while (!_kbhit());

}
