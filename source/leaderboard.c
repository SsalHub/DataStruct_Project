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
    clearScreen();
    //rank(score);
    gotoxy(19, 1);
    fprintf(stdout, "+------------------------+\n");
    gotoxy(19, 2);
    fprintf(stdout, "|          점수판        |\n");
    gotoxy(19, 3);
    fprintf(stdout, "+------------------------+\n");   
    
    for (int a = 1; a < 11; a++) {
        gotoxy(18, 4 + a);
        fprintf(stdout,"%5d위   score : %7d\n", a, rankArr[a - 1]); // 랭킹 출력
    }
    
}
