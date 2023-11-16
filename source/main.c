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

    printString("Hello\nHow Are You\nIm Fine\nThankYou\n", _X_LEFT_, _Y_TOP_);
}

void SunHeok()
{
    /* 임선혁 전용 */

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