#define _CRT_SECURE_NO_WARNINGS
#include "setting_screen.h"

int volume;

void ShowSettings() {
    int Level = 1;

    clearScreen();

    char Option[100] = "------------------설정------------------";
    printString(Option, 20, 9);
    char s1[100] = "1. 음량 설정";
    char s2[100] = "2. 난이도 설정";
    printString(s1, 23, 13);
    printString(s2, 23, 16);

    // 사용자 입력 받기
    char choice = _getch();
}

    /* 사용자의 선택에 따라 동작
    switch (choice) {
    case '1':
        AdjustVolume();
        break;
    case '2':
        SelectLevel(Level);
        break;
    case '3':
        // 설정창 보여주기
        ShowSettings();
        break;
    default:
        fprintf(stdout, "잘못 입력하였습니다.");
        break;
    }
}*/



void AdjustVolume() {
    // 사용자 입력 받기
    int key = _getch();

    // 음량은 10단계
    // 키에 따라 동작 처리
    switch (key) {
    case 72:  // 방향키 위
        volume += 10;
        break;
    case 80:  // 방향키 아래
        volume -= 10;
        break;
    default:
        // 다른 키 입력에 대한 처리 추가
        break;
    }

    // 최소 0
    if (volume < 0) {
        volume = 0;
    }

    // 최대 100
    if (volume > 100) {
        volume = 100;
    }
}

// 난이도 설정
void SelectLevel(int Level) {
    // 사용자 입력 받기
    int key = _getch();

    // 난이도는 4단계
    // 키에 따라 동작 처리
    switch (key) {
    case 72:  // 방향키 위
        Level += 1;
        break;
    case 80:  // 방향키 아래
        Level -= 1;
        break;
    default:
        // 다른 키 입력에 대한 처리 추가
        break;
    }

    // 최소 1
    if (volume < 1) {
        volume = 1;
    }

    // 최대 100
    if (volume > 4) {
        volume = 4;
    }
}