#define _CRT_SECURE_NO_WARNINGS
#include "leaderboard.h"

int rankArr[10] = {0};

//��ŷ ���
void rank(int score) {
    int tmp, x;
    if (rankArr[9] >= score) {

        return;
    }
    if (rankArr[9] <= score)
        rankArr[9] = score;

    for (x = 9; x > 0; x--) {
        if (rankArr[x] > rankArr[x - 1]) {
            tmp = rankArr[x - 1];
            rankArr[x - 1] = rankArr[x];
            rankArr[x] = tmp;
        }
    }
    return;
}
void drawScoreboard() {
    char filter[100];
    clearScreen();
    
    rank(9000);
    rank(345);
    rank(25623);

    printString("+------------------------+", 19, 1);
    printString("|          ������        |", 19, 2);
    printString("+------------------------+", 19, 3);

    for (int a = 1; a < 11; a++) {
        
        sprintf(filter,"%5d��   score : %7d\n", a, rankArr[a - 1]); // ��ŷ ���
        printString(filter, 18, 4 + a);
    }

}
