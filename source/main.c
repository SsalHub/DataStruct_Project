#define _CRT_SECURE_NO_WARNINGS
#include "BaseData.h"
#include "MainMenu.h"
#include "Leaderboard.h"


int main(void) {
    initGame();

    showMainMenu();

    drawScoreboard();

    return 0;
}