#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

int main(void) {
    initGame();

    JaeUk();
    //SunHeok();
    //JunSeong();
    //JunSeo();

    return 0;
}

void JaeUk()
{
    /* 송재욱 전용 */
    char s[64];
    strcpy(s, "문자열");
    printString(s, _ALIGN_CENTER_, _ALIGN_BOTTOM_);
    gotoxy(_ALIGN_RIGHT_, _ALIGN_BOTTOM_);
}

void SunHeok()
{
    /* 임선혁 전용 */
    Pause();
}

void JunSeong()
{
    /* 조준성 전용 */
    drawScoreboard();
}

void JunSeo()
{
    /* 최준서 전용 */
    showMainMenu();
}