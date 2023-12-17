#define _CRT_SECURE_NO_WARNINGS
#include "main_menu.h"


void showMainMenu()
{
    char buffer[64];
    int x, y, len;

    const char* filePath = LOGO_PATH;
    FILE* file = fopen(filePath, "r");
    
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }
    
    gotoxy(_ALIGN_CENTER_, _ALIGN_TOP_);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(file);


    // 메뉴 출력
    gotoxy(20, 16);
    fprintf(stdout, "1. Start Game");

    gotoxy(20, 18);
    fprintf(stdout, "2. Option");

    gotoxy(20, 20);
    fprintf(stdout, "3. Ranking");

    gotoxy(20, 22);
    fprintf(stdout, "4. Exit Game");

    // 사용자 입력 받기
    char choice = _getch();

    // 사용자의 선택에 따라 동작
    switch (choice) {
    case '1':
        // Game start
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
