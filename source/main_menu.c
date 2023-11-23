#define _CRT_SECURE_NO_WARNINGS
#include "main_menu.h"

void showMainMenu()
{
    char buffer[64];
    int x, y, len;

    const char* filePath = "C:\\Users\\junseo\\Desktop\\datastruct\\teamproject\\datastruct_project\\DataStruct_Project\\resources\\title_logo.txt";
    FILE* file = fopen(filePath, "r");
    
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }
    
    gotoxy(10, 10);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(file);
    while (!_kbhit());

}
