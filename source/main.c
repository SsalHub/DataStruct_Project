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
    /* ����� ���� */

    printString("Hello\nHow Are You\nIm Fine\nThankYou\n", _X_LEFT_, _Y_TOP_);
}

void SunHeok()
{
    /* �Ӽ��� ���� */

}

void JunSeong()
{
    /* ���ؼ� ���� */

    drawScoreboard();
}

void JunSeo()
{
    /* ���ؼ� ���� */

    showMainMenu();
}