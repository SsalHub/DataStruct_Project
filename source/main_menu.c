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
    while (!_kbhit());

}
