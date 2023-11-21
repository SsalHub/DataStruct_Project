#define _CRT_SECURE_NO_WARNINGS
#include "leaderboard.h"

int rankArr[10] = {0};

//랭킹 출력
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
    //rank(score);
    
    printString("+------------------------+", 19, 1);
    printString("|          점수판        |", 19, 2);
    printString("+------------------------+", 19, 3);


    for (int a = 1; a < 11; a++) {
        
        sprintf(filter,"%5d위   score : %7d\n", a, rankArr[a - 1]); // 랭킹 출력
        printString(filter, 18, 4 + a);
    }
    
}
