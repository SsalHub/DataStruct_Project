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
    char s[64];
    strcpy(s, "���ڿ�");
    printString(s, _ALIGN_CENTER_, _ALIGN_BOTTOM_);
    gotoxy(_ALIGN_RIGHT_, _ALIGN_BOTTOM_);
}

void SunHeok()
{
    /* �Ӽ��� ���� */
    Pause();
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