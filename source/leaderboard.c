#define _CRT_SECURE_NO_WARNINGS
#include "leaderboard.h"
#define MAX_NAME_LENGTH 20

typedef struct {
    int score;
    char name[MAX_NAME_LENGTH];
} Entry;

void bubbleSort(Entry arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].score < arr[j + 1].score) {
                Entry temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void gotoMain() {
    printString("▶▶ 메인화면으로(아무 키나 누르세요)", 12, 20);
    getch();
    clearScreen();
    showMainMenu();
}

void drawScoreboard() {
    Entry entries[10];  
    char filter[50];
    char str[50];
    clearScreen();

    printString("+------------------------+", 19, 1);
    printString("|          점수판        |", 19, 2);
    printString("+------------------------+", 19, 3);

    const char* fp = "C:\\Users\\user7\\OneDrive\\바탕 화면\\Data_struct_sub\\data_structproject\\DataStruct_Project\\resources\\ranking.dat";
    FILE* file = fopen(fp, "r");

    if (file == NULL) {
        printString("파일 열기 실패\n", 19, 1);
        exit(1);
    }

    int rank = 0;
    while (fgets(filter, sizeof(filter), file) != NULL && rank < 10) {
        char* scoreToken = strtok(filter, " ");
        char* nameToken = strtok(NULL, " \n");

        if (scoreToken != NULL && nameToken != NULL) {
            int score = atoi(scoreToken);
            
            entries[rank].score = score;
            strcpy(entries[rank].name, nameToken);
            rank++;
        }
    }

    fclose(file);

   
    bubbleSort(entries, rank);

    for (int i = 0; i < rank; i++) {
        sprintf(str, "%2d위  score : %5d name : %s\n", i + 1, entries[i].score, entries[i].name);
        printString(str, 16, 4 + i);
    }

    gotoMain();
}