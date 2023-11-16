#define _CRT_SECURE_NO_WARNINGS
#include "main_menu.h"

void showMainMenu()
{
    char buffer[64];
    int x, y, len;

    strcpy(buffer, "Main Menu");
    printString(buffer, _X_CENTER_, _Y_CENTER_);

    strcpy(buffer, "A        D      A      N   N CCCCC EEEEE   OOOOO FFFFF");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, _Y_TOP_);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "A A      D  D   A A    NN  N C     E       O   O F    ");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, 2);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "AAAA     D    D AAAA   N N N C     EEEEE   O   O FFFFF");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, 3);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "A   A    D  D   A   A  N  NN C     E       O   O F    ");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, 4);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "A    A   D      A    A N   N CCCCC EEEEE   OOOOO F    ");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, 5);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "FFFFF IIIII RRRRR EEEEE   IIIII CCCCC EEEEE");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, 7);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "F       I   R   R E         I   C     E    ");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, 8);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "FFFFF   I   RRRRR EEEEE     I   C     EEEEE");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, 9);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "F       I   R R   E         I   C     E    ");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, 10);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "F     IIIII R   R EEEEE   IIIII CCCCC EEEEE");
    len = strlen(buffer);
    gotoxy(_X_CENTER_, 11);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "Press Any Key.");
    printString(buffer, _X_CENTER_, _Y_BOTTOM_);
    while (!_kbhit());

}
