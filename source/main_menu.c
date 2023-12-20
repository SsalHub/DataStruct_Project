#define _CRT_SECURE_NO_WARNINGS
#include "main_menu.h"
#include <errno.h>


void showMainMenu()
{
    clearScreen();
    char buffer[64];
    int x, y, len;

    //const char* filePath = LOGO_PATH;
    FILE* file = fopen("./title_logo.txt", "r");
    
    if (file == NULL) {
        printf("[%d] 파일을 열 수 없습니다.\n", errno);
        return 1;
    }
    
    gotoxy(_ALIGN_CENTER_, _ALIGN_TOP_);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(file);

    // 메뉴 출력
    strcpy(buffer, "1. Start Game");
    printString(buffer, _ALIGN_CENTER_, 12);
    
    strcpy(buffer, "2. Option");
    printString(buffer, _ALIGN_CENTER_, 14);
    
    strcpy(buffer, "3. Ranking");
    printString(buffer, _ALIGN_CENTER_, 16);

    strcpy(buffer, "4. Exit Game");
    printString(buffer, _ALIGN_CENTER_, 18);

    // 사용자 입력 받기
    char choice = _getch();

    // 사용자의 선택에 따라 동작
    switch (choice) {
    case '1':
        loadStageSelect();
        break;
    case '2':
        // Option
        ShowSettings();
        break;
    case '3':
        // Ranking
        drawScoreboard();
        break;
    case '4':
        // exit
        system("cls");
        break;
    default:
        fprintf(stdout, "잘못 입력하였습니다.");
        break;
    }
    while (!_kbhit());
}
