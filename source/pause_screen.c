#define _CRT_SECURE_NO_WARNINGS
#include "pause_screen.h"
#include <conio.h>

int CurserPoint = 13;

void choice(selectIndex) {
    switch (selectIndex) {
    case '1':
        clearScreen();
        char x1[100] = "���ư���";
        printString(x1, 20, 9);
        break;
    case '2':
        ShowSettings();
        break;
    case '3':
        clearScreen();
        char x3[100] = "�������� ����";
        printString(x3, 20, 9);
        break;
    case '4':
        showMainMenu();
        break;
    default:
        clearScreen();
        char x5[100] = "�ٽ� ��������";
        printString(x5, 20, 9);
        break;
        break;
    }
}

void Pause() {
    clearScreen(); // ȭ���� ���� ���ο� ȭ�� ���
    const int MAX_SELECT = 4;
    int selectIndex = 1;
    char input;

    // ���� Ŀ�� ��ġ�� ���� Ŀ�� ���
    char cursor[10] = "��";
    char Space[10] = "       ";
    printString(cursor, 19, 13 + 3 * (selectIndex - 1));

    // ȭ�� �۾� ���
    char Pause[100] = "P A U S E";
    char score[100] = "Current Score : ";
    char s1[100] = "1 : Resume";
    char s2[100] = "2 : Option";
    char s3[100] = "3 : Back to Stage Select";
    char s4[100] = "4 : Back to Main Menu";
    printString(Pause, 26, 4);
    printString(score, 20, 9);
    printString(s1, 23, 13);
    printString(s2, 23, 16);
    printString(s3, 23, 19);
    printString(s4, 23, 22);

    //Ű����� �Է¹ޱ�
    while (1) {
        if (_kbhit()) {
            input = _getch();
            switch (input) {
            case '1': //�ִ밪�� 4
                printString(cursor, 19, CurserPoint);
                printString(Space, 19, CurserPoint + 3);
                printString(Space, 19, CurserPoint + 6);
                printString(Space, 19, CurserPoint + 9);
                choice(input);
                Sleep(10);
                break;
            case '2': //�ּҰ��� 0
                printString(cursor, 19, CurserPoint + 3);
                printString(Space, 19, CurserPoint);
                printString(Space, 19, CurserPoint + 6);
                printString(Space, 19, CurserPoint + 9);
                choice(input);
                Sleep(10);
                break;
            case '3': //����Ű ������ ��
                printString(cursor, 19, CurserPoint + 6);
                printString(Space, 19, CurserPoint + 3);
                printString(Space, 19, CurserPoint);
                printString(Space, 19, CurserPoint + 9);
                choice(input);
                Sleep(10);
                break;
            case '4': //�ּҰ��� 0
                printString(cursor, 19, CurserPoint + 9);
                printString(Space, 19, CurserPoint + 3);
                printString(Space, 19, CurserPoint + 6);
                printString(Space, 19, CurserPoint);
                choice(input);
                Sleep(10);
                break;
            default:
                break;
            }
        }
    }

}
