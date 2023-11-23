#define _CRT_SECURE_NO_WARNINGS
#include "leaderboard.h"


void drawScoreboard() {
    char filter[50];
    char str[50];
    clearScreen();

    printString("+------------------------+", 19, 1);
    printString("|          ������        |", 19, 2);
    printString("+------------------------+", 19, 3);

    const char* fp = "C:\\Users\\user7\\OneDrive\\���� ȭ��\\Data_struct_sub\\data_structproject\\DataStruct_Project\\resources\\ranking.dat";
    FILE* file = fopen(fp, "r");

    if (file == NULL) {
        printString("���� ���� ����\n", 19, 1);
        exit(1);
    }
    int rank = 1; 
    while (fgets(filter, sizeof(filter), file) != NULL) {
        
        char* scoreToken = strtok(filter, " ");
        char* nameToken = strtok(NULL, " \n");

        if (scoreToken != NULL && nameToken != NULL) {
           
            int score = atoi(scoreToken);


            sprintf(str, "%2d��  score : %5d name : %s\n", rank, score, nameToken);
            printString(str, 16, rank + 3); 

            rank++;
            if (rank > 10) {
                break; 
            }
        }
    }

    fclose(file);
}
