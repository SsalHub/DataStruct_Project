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
        printf("[%d] ������ �� �� �����ϴ�.\n", errno);
        return 1;
    }
    
    gotoxy(_ALIGN_CENTER_, _ALIGN_TOP_);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(file);

    // �޴� ���
    strcpy(buffer, "1. Start Game");
    printString(buffer, _ALIGN_CENTER_, 12);
    
    strcpy(buffer, "2. Option");
    printString(buffer, _ALIGN_CENTER_, 14);
    
    strcpy(buffer, "3. Ranking");
    printString(buffer, _ALIGN_CENTER_, 16);

    strcpy(buffer, "4. Exit Game");
    printString(buffer, _ALIGN_CENTER_, 18);

    // ����� �Է� �ޱ�
    char choice = _getch();

    // ������� ���ÿ� ���� ����
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
        fprintf(stdout, "�߸� �Է��Ͽ����ϴ�.");
        break;
    }
    while (!_kbhit());
}
