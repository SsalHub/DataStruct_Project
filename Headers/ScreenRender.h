#pragma once

#include <stdbool.h>
#include <process.h>

#include "BaseData.h"

typedef struct ScreenBuffer
{
	HANDLE buffer[2];
	int currentIndex;
} ScreenBuffer;

typedef struct StageSelectBox
{
	COORD pos;
	char buffer[_SCREEN_WIDTH_];
	int stageIndex;
} StageSelectBox;

extern ScreenBuffer screenBuffer;

/* Basic screen functions */
void initScreen();
void printScreen(void (void));
void printMainMenuScreen(int);
void printStageSelectScreen(MapData*, int, bool, bool);
void printStageLoadingScreen(char*);
void printStageMapScreen(MapData*, const int);
void printStageResultScreen(Ranking*, const int, const int, bool, bool);
void printStageClearScreen();
void printPauseScreen(int);
void clearScreen();
void printSaveScreen(Ranking);
void swapScreenIndex();
void fillColorToScreen(ConsoleColor, ConsoleColor);
void setColor(ConsoleColor, ConsoleColor);
void releaseScreen();
void showRedEffect(); 	// Red Effect

/* Render functions */
void renderString(char*, COORD);
void renderMainMenuScreen(int);					// MainMenu
void renderStageSelectScreen(MapData*, int, bool, bool);	// Stage Select
void renderStageLoadingScreen(char*, int);					// Stage Loading
void renderConfirmRestartScreen();							// Confirm Stage Restart
void renderStageClearScreen(int, int);						// Stage Clear
void renderStageMapScreen(MapData*, const int);				// Stage Map Data
void renderStageResultScreen(Ranking*, const int, const int, bool, bool);
void renderPauseScreen(int);								// Pause while playing stage
void renderSaveScreen(Ranking);
void renderPlayer(COORD, ConsoleColor);						// Player only, with player personal color

