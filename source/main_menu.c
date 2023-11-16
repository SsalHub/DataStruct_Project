#define _CRT_SECURE_NO_WARNINGS
#include "main_menu.h"

void showMainMenu()
{
    char buffer[64];
    int x, y, len;

    strcpy(buffer, "Main Menu");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, _ALIGN_CENTER_, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "A        D      A      N   N CCCCC EEEEE   OOOOO FFFFF");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, _ALIGN_TOP_, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "A A      D  D   A A    NN  N C     E       O   O F    ");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, 2, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "AAAA     D    D AAAA   N N N C     EEEEE   O   O FFFFF");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, 3, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "A   A    D  D   A   A  N  NN C     E       O   O F    ");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, 4, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "A    A   D      A    A N   N CCCCC EEEEE   OOOOO F    ");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, 5, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "FFFFF IIIII RRRRR EEEEE   IIIII CCCCC EEEEE");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, 7, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "F       I   R   R E         I   C     E    ");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, 8, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "FFFFF   I   RRRRR EEEEE     I   C     EEEEE");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, 9, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "F       I   R R   E         I   C     E    ");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, 10, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "F     IIIII R   R EEEEE   IIIII CCCCC EEEEE");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, 11, len);
    fprintf(stdout, "%s\n", buffer);

    strcpy(buffer, "Press Any Key.");
    len = strlen(buffer);
    gotoxyDetailed(_ALIGN_CENTER_, _ALIGN_BOTTOM_, len);
    fprintf(stdout, "%s\n", buffer);
    while (!_kbhit());

}
