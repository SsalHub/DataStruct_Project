#ifndef __LEADERBOARD__
#define __LEADERBOARD__

#include "../utils/utility.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#define RANKING_PATH "..\\resources\\ranking.dat"
#define MAX_NAME_LENGTH 20

typedef struct {
    int score;
    char name[MAX_NAME_LENGTH];
} Entry;

void drawScoreboard();

#endif