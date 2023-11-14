#define _CRT_SECURE_NO_WARNINGS
#include "leaderboard.h"

void drawScoreboard() {
    clearScreen();
    gotoxy(19, 1);
    fprintf(stdout, "+------------------------+\n");
    gotoxy(19, 2);
    fprintf(stdout, "|          Á¡¼öÆÇ        |\n");
    gotoxy(19, 3);
    fprintf(stdout, "+------------------------+\n");
    
}
