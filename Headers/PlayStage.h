#pragma once

#include "BaseData.h"
#include "UtilData.h"
#include "ScreenRender.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <process.h>
#include <Windows.h>

void playStage();
int loadStageSelect(int);
Flag playGame(MapData*, int*);
Flag confirmRestartStage();
int pauseGame();
void stageClear(int);
void showResultScreen(const int, const int);
void showSaveScreen(Ranking*, const int, const int);