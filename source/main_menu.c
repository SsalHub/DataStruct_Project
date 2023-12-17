#define _CRT_SECURE_NO_WARNINGS
#include "main_menu.h"


void showMainMenu()
{
    char buffer[64];
    int x, y, len;

    const char* filePath = LOGO_PATH;
    FILE* file = fopen(filePath, "r");
    
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }
    
    gotoxy(_ALIGN_CENTER_, _ALIGN_TOP_);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(file);


    // �޴� ���
    gotoxy(20, 16);
    fprintf(stdout, "1. Start Game");

    gotoxy(20, 18);
    fprintf(stdout, "2. Option");

    gotoxy(20, 20);
    fprintf(stdout, "3. Ranking");

    gotoxy(20, 22);
    fprintf(stdout, "4. Exit Game");

    // ����� �Է� �ޱ�
    char choice = _getch();

    // ������� ���ÿ� ���� ����
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
        fprintf(stdout, "�߸� �Է��Ͽ����ϴ�.");
        break;
    }
    while (!_kbhit());
}
