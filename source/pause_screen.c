#define _CRT_SECURE_NO_WARNINGS
#include "pause_screen.h"



void Pause()
{

    clearScreen(); // 화면을 지워 새로운 화면 출력
    const int MAX_SELECT = 4;
    int selectIndex = 0;
    char input;

    //화면 글씨 출력
    char Pause[100] = "P A U S E";
    printString(Pause, 26, 4);
    char score[100] = "Current Score : ";
    printString(score, 20, 9);
    char s1[100] = "1 : Resume";
    printString(s1, 23, 13);
    char s2[100] = "2 : Option";
    printString(s2, 23, 16);
    char s3[100] = "3 : Back to Stage Select";
    printString(s3, 23, 19);
    char s4[100] = "4 : Back to Main Menu";
    printString(s4, 23, 22);

    //키보드로 입력받기
    while (1) {
        if (_kbhit()) {
            input = _getch();
            switch (input) {
            case _DOWN_: //최대값은 4
                if (selectIndex + 1 <= MAX_SELECT)
                    selectIndex += 1;
                Sleep(10);
                break;
            case _UP_: //최소값은 0
                if (selectIndex - 1 >= 1)
                    selectIndex -= 1;
                Sleep(10);
                break;
            /*
            case _CARRIAGE_RETURN_: //엔터키 눌렀을 때
                choice(selectIndex);
                Sleep(10);
                break;
                */
            default:
                break;
            }
        }
    }

}
