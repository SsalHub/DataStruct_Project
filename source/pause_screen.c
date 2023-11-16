#define _CRT_SECURE_NO_WARNINGS
#include "pause_screen.h"

void Pause()
{
    clearScreen(); // ȭ���� ���� ���ο� ȭ�� ���

    // ����� "PAUSE" ���
    int pauseTextLength = strlen("*********PAUSE********");
    int pauseX = (_SCREEN_WIDTH_ - pauseTextLength) / 2;
    int pauseY = _SCREEN_HEIGHT_ / 4;
    gotoxy(pauseX, pauseY);
    fprintf(stdout, "*********PAUSE********");

    // ���� �� ���̵� ���
    gotoxy(20, pauseY + 5);
    fprintf(stdout, "���� : ");

    gotoxy(40, pauseY + 5);
    fprintf(stdout, "���̵� : ");

    // �޴� ���
    gotoxy(20, pauseY + 10);
    fprintf(stdout, "1. �������� ���ư���");

    gotoxy(40, pauseY + 10);
    fprintf(stdout, "2. ���� ����");

    gotoxy(30, pauseY + 25);
    fprintf(stdout, "3. ����");

    // ����� �Է� �ޱ�
    char choice = _getch();

    // ������� ���ÿ� ���� ����
    switch (choice) {
    case '1':
        // �������� ���ư���
        break;
    case '2':
        // ���� ����
        break;
    case '3':
        // ����â �����ֱ�
        ShowSettings();
        break;
    default:
        fprintf(stdout, "�߸� �Է��Ͽ����ϴ�.");
        break;
    }
}