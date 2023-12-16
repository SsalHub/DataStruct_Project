#define _CRT_SECURE_NO_WARNINGS
#include "pause_screen.h"
#include <conio.h>

int CurserPoint = 13;

void choice(selectIndex) {
    switch (selectIndex) {
    case '1':
        clearScreen();
        char x1[100] = "돌아가기";
        printString(x1, 20, 9);
        break;
    case '2':
        ShowSettings();
        break;
    case '3':
        clearScreen();
        char x3[100] = "스테이지 선택";
        printString(x3, 20, 9);
        break;
    case '4':
        showMainMenu();
        break;
    default:
        clearScreen();
        char x5[100] = "다시 누르세요";
        printString(x5, 20, 9);
        break;
        break;
    }
}

void Pause() {
    clearScreen(); // 화면을 지워 새로운 화면 출력
    const int MAX_SELECT = 4;
    int selectIndex = 1;
    char input;

    // 현재 커서 위치에 따라 커서 출력
    char cursor[10] = "▶";
    char Space[10] = "       ";
    printString(cursor, 19, 13 + 3 * (selectIndex - 1));

    // 화면 글씨 출력
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

    //키보드로 입력받기
    while (1) {
        if (_kbhit()) {
            input = _getch();
            switch (input) {
            case '1': //최대값은 4
                printString(cursor, 19, CurserPoint);
                printString(Space, 19, CurserPoint + 3);
                printString(Space, 19, CurserPoint + 6);
                printString(Space, 19, CurserPoint + 9);
                choice(input);
                Sleep(10);
                break;
            case '2': //최소값은 0
                printString(cursor, 19, CurserPoint + 3);
                printString(Space, 19, CurserPoint);
                printString(Space, 19, CurserPoint + 6);
                printString(Space, 19, CurserPoint + 9);
                choice(input);
                Sleep(10);
                break;
            case '3': //엔터키 눌렀을 때
                printString(cursor, 19, CurserPoint + 6);
                printString(Space, 19, CurserPoint + 3);
                printString(Space, 19, CurserPoint);
                printString(Space, 19, CurserPoint + 9);
                choice(input);
                Sleep(10);
                break;
            case '4': //최소값은 0
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
