#include "MainMenu.h"

int main()
{
    initGame();
    showMainMenu();

    return 0;
}

void showMainMenu()
{
    char buffer[64];
    int x, y, len;

    strcpy(buffer, "Main Menu");
    len = strlen(buffer);
    x = (_SCREEN_WIDTH_ - len) * 0.5f + 1;
    y = _SCREEN_HEIGHT_ * 0.5f;
    gotoxy(x, y);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "Press Any Key.");
    len = strlen(buffer);
    x = (_SCREEN_WIDTH_ - len) * 0.5f + 1;
    y = _SCREEN_HEIGHT_ * 0.5f;
    gotoxy(x, y);
    fprintf(stdout, "Press Any Key.\n");
    while (!onKeyboardInput());

}
