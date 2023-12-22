#include "../Headers/ScreenRender.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

#include "../Headers/BaseData.h"
#include "../Headers/UtilData.h"
#include "../Headers/ExceptionHandler.h"

ScreenBuffer screenBuffer;

void initScreen()
{
	CONSOLE_CURSOR_INFO cursor;
	char screenInitCommand[50] = "";

    sprintf(screenInitCommand, "mode con:cols=%d lines=%d", _SCREEN_WIDTH_, _SCREEN_HEIGHT_);
	system(screenInitCommand);
	SetConsoleTitle("Sokoban in Hansung Univ.");

	/* Cursor */
	cursor.dwSize = 1;
	cursor.bVisible = false;

	screenBuffer.currentIndex = 0;
	screenBuffer.buffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleCursorInfo(screenBuffer.buffer[0], &cursor);
	screenBuffer.buffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleCursorInfo(screenBuffer.buffer[1], &cursor);
}

void printScreen(void render(void))
{
	clearScreen();
	render();
	SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
	swapScreenIndex();
}

void printMainMenuScreen(int selectIndex)
{
	clearScreen();
	renderMainMenuScreen(selectIndex);
	SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
	swapScreenIndex();
}

void printStageSelectScreen(MapData* map, int maxStage, bool bLeftDown, bool bRightDown)
{
	clearScreen();
	renderStageSelectScreen(map, maxStage, bLeftDown, bRightDown);
	SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
	swapScreenIndex();
}

void printStageLoadingScreen(char* target)
{
	const int LOOPMAX = 3;
	int i;

	for (i = 0; i < LOOPMAX; i++)
	{
		clearScreen();
		renderStageLoadingScreen(target, i);
		SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
		swapScreenIndex();
		WaitForSeconds(0.2);
	}
}

void printStageMapScreen(MapData* pMap, const int movement)
{
	clearScreen();
	renderStageMapScreen(pMap, movement);
	SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
	swapScreenIndex();
}

void printStageResultScreen(Ranking* ranking, const int stage, const int score, bool bLeftDown, bool bRightDown)
{
	clearScreen();
	renderStageResultScreen(ranking, stage, score, bLeftDown, bRightDown);
	SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
	swapScreenIndex();
}

void printStageClearScreen(int stageIndex)
{
	const int LOOPMAX = 7;
	int i = 0;

	for (i = 0; i < LOOPMAX; i++)
	{
		clearScreen();
		renderStageClearScreen(stageIndex, i);
		SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
		swapScreenIndex();
		WaitForSeconds(0.1);
	}
}

void printPauseScreen(int selectIndex)
{
	clearScreen();
	renderPauseScreen(selectIndex);
	SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
	swapScreenIndex();
}

void printSaveScreen(Ranking rank)
{
	clearScreen();
	renderSaveScreen(rank);
	SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
	swapScreenIndex();
}

void clearScreen()
{
	COORD zero = { 0, 0 };
	DWORD dw;
	char bufferString[(_SCREEN_WIDTH_*2)*_SCREEN_HEIGHT_+1];
	int i, j;

	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], zero);
	SetConsoleTextAttribute(screenBuffer.buffer[screenBuffer.currentIndex], _WHITE_ | (_BLACK_ << 4));
	bufferString[0] = '\0';
	for (i = 0; i < _SCREEN_HEIGHT_; i++)
	{
		for (j = 0; j < _SCREEN_WIDTH_; j++)
		{
			strcat(bufferString, " ");
		}
		strcat(bufferString, "\n");
	}
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], bufferString, strlen(bufferString), &dw, NULL);
}

void swapScreenIndex()
{
	screenBuffer.currentIndex = !(screenBuffer.currentIndex);
}

void fillColorToScreen(ConsoleColor bColor, ConsoleColor tColor)
{
	COORD zero = { 0, 0 };
	DWORD dw;
	char bufferString[(_SCREEN_WIDTH_+1)*_SCREEN_HEIGHT_+1] = "";
	int i, currIdx;

	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], zero);
	SetConsoleTextAttribute(screenBuffer.buffer[screenBuffer.currentIndex], tColor | (bColor << 4));
	bufferString[0] = '\0';
	for (i = 0; i < _SCREEN_HEIGHT_; i++)
	{
        currIdx = i * (_SCREEN_WIDTH_ + 1);
	    memset(bufferString+currIdx, ' ', _SCREEN_WIDTH_*sizeof(char));
		bufferString[currIdx+_SCREEN_WIDTH_] = '\n';
	}
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], bufferString, strlen(bufferString), &dw, NULL);
}

void setColor(ConsoleColor bColor, ConsoleColor tColor)
{
	SetConsoleTextAttribute(screenBuffer.buffer[screenBuffer.currentIndex], tColor | (bColor << 4));
}

void releaseScreen()
{
	CloseHandle(screenBuffer.buffer[0]);
	CloseHandle(screenBuffer.buffer[1]);
}

/* Red Effect */
void showRedEffect()
{
	fillColorToScreen(_RED_, _WHITE_);
	SetConsoleActiveScreenBuffer(screenBuffer.buffer[screenBuffer.currentIndex]);
	swapScreenIndex();
	WaitForSeconds(0.05);
}

void renderString(char* str, COORD pos)
{
	DWORD dw;
	char* nextLine;

	nextLine = strtok(str, "\n");
	while (nextLine != NULL)
	{
		SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], pos);
		WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], nextLine, strlen(nextLine), &dw, NULL);
		nextLine = strtok(NULL, "\n");
		pos.Y++;
	}
}

/* MainMenu */
void renderMainMenuScreen(int selectIndex)
{
	ConsoleColor bColor = _HOTPINK_, tColor = _BLACK_, tTitleColor = _SKY_, tLogoColor = _GREEN_, tSelColor = _BLUE_;
	COORD titlePos = { 0, (int)(_SCREEN_HEIGHT_ * 0.2) };
	COORD contentPos[2], selectedPos;
	DWORD dw;
	char title[_SCREEN_WIDTH_], content[2][64], selectedChar[5] = "▶ ";
	char bufferString[(_MAP_WIDTH_*2)*_MAP_HEIGHT_+1] = "";
	char* nextLine;
	int i, contentPosY = _SCREEN_HEIGHT_ * 0.75;

	fillColorToScreen(bColor, tColor);

	setColor(bColor, tTitleColor);
	sprintf(title, "SOKOBAN in Hansung Univ.");
	titlePos.X = (_SCREEN_WIDTH_ - strlen(title)) * 0.5;
	titlePos.Y++;
	renderString(title, titlePos);

	titlePos.Y += 2;

	setColor(bColor, tLogoColor);
	sprintf(title, "┏━━━━━┳━━━━━┳┓┏━━━┳━━━━━┳━━━━┓┏━━━━━┳━┓  ┏┓ ");
	titlePos.X = (_SCREEN_WIDTH_ - (strlen(title) * 0.5)) * 0.5 + 8;
	titlePos.Y++;
	renderString(title, titlePos);
	sprintf(title, "┃┏━━━┓┃┏━━━┓┃┃┃┏━━┫┏━━━┓┃┏━━┓┃┃┏━━━┓┃┃┗━┓┃┃ ");
	titlePos.Y++;
	renderString(title, titlePos);
	sprintf(title, "┃┗━━━━┫┃   ┃┃┗┛┛  ┃┃   ┃┃┗━━┛┗┫┃   ┃┃┏━┓┗┛┃ ");
	titlePos.Y++;
	renderString(title, titlePos);
	sprintf(title, "┗━━━━┓┃┃   ┃┃┏┓┃  ┃┃   ┃┃┏━━━┓┃┗━━━┛┃┃ ┗━┓┃ ");
	titlePos.Y++;
	renderString(title, titlePos);
	sprintf(title, "┃┗━━━┛┃┗━━━┛┃┃┃┗━━┫┗━━━┛┃┗━━━┛┃┏━━━┓┃┃   ┃┃ ");
	titlePos.Y++;
	renderString(title, titlePos);
	sprintf(title, "┗━━━━━┻━━━━━┻┛┗━━━┻━━━━━┻━━━━━┻┛   ┗┻┛   ┗┛ ");
	titlePos.Y++;
	renderString(title, titlePos);

	titlePos.Y += 2;

	setColor(bColor, tTitleColor);
	sprintf(title, "Sokoban!");
	titlePos.X = (_SCREEN_WIDTH_ - strlen(title)) * 0.5;
	titlePos.Y++;
	renderString(title, titlePos);

	sprintf(content[0], "Game Start");
	contentPos[0].X = (_SCREEN_WIDTH_ - strlen(content[0])) * 0.5;
	contentPos[0].Y = contentPosY;
	sprintf(content[1], "Exit Game");
	contentPos[1].X = (_SCREEN_WIDTH_ - strlen(content[1])) * 0.5;
	contentPos[1].Y = contentPosY + 1;

	for (i = 0; i < 2; i++)
	{
		if (i == selectIndex)
		{
			selectedPos.X = contentPos[i].X - 3;
			selectedPos.Y = contentPos[i].Y;
	        setColor(bColor, tSelColor);
		}
		else
		{
	        setColor(bColor, tColor);
		}
		SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], contentPos[i]);
		WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], content[i], strlen(content[i]), &dw, NULL);
	}
	setColor(bColor, tSelColor);
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], selectedPos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], selectedChar, strlen(selectedChar), &dw, NULL);
}

/* Stage Select */
void renderStageSelectScreen(MapData* map, int maxStage, bool bLeftDown, bool bRightDown)
{
	ConsoleColor bColor = _HOTPINK_, bBlankColor = _DARK_PURPLE_, tColor = _BLACK_, bStructColor = _DARK_PURPLE_, tStructColor = _GREEN_;
	COORD leftArrowPos = { _SCREEN_WIDTH_ * 0.08, _SCREEN_HEIGHT_ * 0.5 }, rightArrowPos = { _SCREEN_WIDTH_ * 0.92, _SCREEN_HEIGHT_ * 0.5 };
	COORD titlePos = { 0, _SCREEN_HEIGHT_ * 0.1 };
	COORD structurePos = { (_SCREEN_WIDTH_ - (_MAP_WIDTH_ * 1.5)) * 0.5, (_SCREEN_HEIGHT_ - _MAP_HEIGHT_) * 0.5 + 2 };
	COORD playerPos, halfPos;
	DWORD dw;
	char leftArrowStr[5] = "◀", rightArrowStr[5] = "▶";
	char title[_SCREEN_WIDTH_ * 5], structure[(int)(_MAP_WIDTH_*1.5+1)*_MAP_HEIGHT_+1];
	char* halfScreen = structure;
	int i, j, currIdx, halfWidth = _SCREEN_WIDTH_ * 0.5;

	fillColorToScreen(bColor, tColor);

	/* Print Each Arrows. */
	setColor(bColor, tColor);
	if (1 < map->stageIndex)
	   renderString(leftArrowStr, leftArrowPos);
	if (map->stageIndex < maxStage)
	   renderString(rightArrowStr, rightArrowPos);

	/* Print Title. */
	title[0] = '\0';
	sprintf(title, "%s┌────────────────────────────┐ \n", title);
	titlePos.X = (_SCREEN_WIDTH_ - (strlen(title) * 0.5)) * 0.6;
	sprintf(title, "%s│          STAGE %03d         │ \n", title, map->stageIndex);
	sprintf(title, "%s└────────────────────────────┘ \n", title);
	renderString(title, titlePos);

	/* Print Stage Structure. */
	setColor(bBlankColor, tColor);
	for (i = 0; i < _MAP_HEIGHT_; i++)
	{
		currIdx = i * (int)(_MAP_WIDTH_ * 1.5 + 1);
		memset(structure + currIdx, ' ', (int)(_MAP_WIDTH_ * 1.5) * sizeof(char));
		structure[currIdx+(int)(_MAP_WIDTH_*1.5)] = '\n';
	}
	structure[(int)(_MAP_WIDTH_*1.5+1)*_MAP_HEIGHT_] = '\0';
	renderString(structure, structurePos);

	setColor(bStructColor, tStructColor);
	structure[0] = '\0';
	for (i = 0; i < map->width+2; i++)
	{
	   strcat(structure, character[_OUT_OF_MAP_]);
    }
	strcat(structure, "\n");
	for (i = 0; i < map->height; i++)
	{
	   strcat(structure, character[_OUT_OF_MAP_]);
	   for (j = 0; j < map->width; j++)
	   {
	       switch (map->originMap[i][j])
	       {
	           case _NONE_:		
	               strcat(structure, character[_NONE_]);
	               break;
	           case _PLAYER_:
	               strcat(structure, character[_NONE_]);
	               break;
	           case _WALL_:
	               strcat(structure, character[_WALL_]);
	               break;
	           case _BALL_:
	               strcat(structure, character[_BALL_]);
	               break;
	           case _EMPTY_BOX_:
	               strcat(structure, character[_EMPTY_BOX_]);
	               break;
	           case _FILLED_BOX_:
	               strcat(structure, character[_FILLED_BOX_]);
	               break;
           }
       }
	   strcat(structure, character[_OUT_OF_MAP_]);
	   strcat(structure, "\n");
    }
	strcat(structure, "\n");
	for (i = 0; i < map->width+2; i++)
	{
	   strcat(structure, character[_OUT_OF_MAP_]);
    }

    structurePos.X = (_SCREEN_WIDTH_ - ((map->width + 2) * 2)) * 0.5;
    structurePos.Y = (_SCREEN_HEIGHT_ - map->height) * 0.5 + 1;
	renderString(structure, structurePos);
	
	/* Fill color if arrow key down. */
	halfScreen[0] = '\0';
	if (bLeftDown || bRightDown)
	{
		for (i = 0; i < _SCREEN_HEIGHT_; i++)
		{
			currIdx = i * (halfWidth + 1);
			memset(halfScreen + currIdx, ' ', halfWidth * sizeof(char));
			halfScreen[currIdx+halfWidth] = '\n';
		}

		setColor(_YELLOW_, tColor);
		if (bLeftDown)
		{
			halfPos.X = 0;
			halfPos.Y = 0;
			renderString(halfScreen, halfPos);
		}
		else
		{
			halfPos.X = halfWidth;
			halfPos.Y = 0;
			renderString(halfScreen, halfPos);
		}
	}
//	playerPos.X = structurePos.X + (map->playerBeginPos.X + 1) * 2;
//	playerPos.Y = structurePos.Y + (map->playerBeginPos.Y + 1);
//	renderPlayer(playerPos, bStructColor, _YELLOW_);
}

/* Stage Loading */
void renderStageLoadingScreen(char* target, int loop)
{
	ConsoleColor bColor = _SKYBLUE_, tColor = _BLACK_;
	COORD pos = { 0, _SCREEN_HEIGHT_ * 0.5};
	DWORD dw;
	char loadingText[_SCREEN_WIDTH_+1];
	int i, slen;

	fillColorToScreen(bColor, tColor);

	setColor(bColor, tColor);
	sprintf(loadingText, "Loading %s", target);
	for (i = 0; i < loop; i++)
		strcat(loadingText, " .");

	slen = strlen(loadingText);

	pos.X = (_SCREEN_WIDTH_ - slen) * 0.5;
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], pos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], loadingText, slen, &dw, NULL);
}

/* Confirm Stage Restart */
void renderConfirmRestartScreen()
{
	ConsoleColor bColor = _DARK_PURPLE_, tColor = _WHITE_, selColor = _YELLOW_;
	COORD titlePos = { 0, (int)(_SCREEN_HEIGHT_ * 0.3) }, contentPos = { 0, (int)(_SCREEN_HEIGHT_ * 0.7) };
	DWORD dw;
	char title[64] = "", content[64] = "";
	int i, j;

	fillColorToScreen(bColor, tColor);

	sprintf(title, 		"Restart This Stage?"	      );
	sprintf(content, 	"← CONTINUE     |     RESTART →"	);

	titlePos.X = (int)((_SCREEN_WIDTH_ - strlen(title)) * 0.5);
	contentPos.X = (int)((_SCREEN_WIDTH_ - strlen(content)) * 0.5);

	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], titlePos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], title, strlen(title), &dw, NULL);
	setColor(bColor, selColor);
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], contentPos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], content, strlen(content), &dw, NULL);
}

/* Stage Clear */
void renderStageClearScreen(int stageIndex, int loop)
{
	ConsoleColor bColor = _LIGHT_YELLOW_, tColor = _BLACK_;
	COORD pos = { 0, (int)(_SCREEN_HEIGHT_ * 0.5)};
	DWORD dw;
	char stageClearText[_SCREEN_WIDTH_+1];
	int i, slen;

	fillColorToScreen(bColor, tColor);

	setColor(bColor, tColor);
	sprintf(stageClearText, "Stage%03d Clear", stageIndex);
	for (i = 0; i < loop; i++)
		strcat(stageClearText, " !");

	slen = strlen(stageClearText);

	pos.X = (_SCREEN_WIDTH_ - slen) * 0.5;
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], pos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], stageClearText, slen, &dw, NULL);
}

/* Stage Map Data */
void renderStageMapScreen(MapData* map, const int movement)
{
	ConsoleColor bColor = _HOTPINK_, bBlankColor = _DARK_PURPLE_, tColor = _BLUE_, tPlayerColor = _YELLOW_;
	ConsoleColor bToolColor = _BLACK_, tToolColor = _WHITE_;
	int centerAlignX = ((_SCREEN_WIDTH_)-((map->width+2)*2))*0.5, centerAlignY = (_SCREEN_HEIGHT_ - map->height)*0.5-1;
	COORD centeredMapPos = { centerAlignX, centerAlignY }, playerPos = { centeredMapPos.X+((map->currPlayerPos.X+1)*2), centeredMapPos.Y+map->currPlayerPos.Y+1 };
	COORD tooltipPos = { _SCREEN_WIDTH_ * 0.04, _SCREEN_HEIGHT_ * 0.5 - 6 }, movementPos = { _SCREEN_WIDTH_ * 0.76, _SCREEN_HEIGHT_ * 0.5 - 2 };
	DWORD dw;
	char stageMapString[(_SCREEN_WIDTH_*2+1)*_SCREEN_HEIGHT_+1], tooltip[5][32];
	int i, j, currIdx, tooltipX, movementX;

	fillColorToScreen(bBlankColor, tColor);

	/* Write rendered stage(= map) data to HANDLE(= screen buffer). */
	stageMapString[0] = '\0';
	for (i = 0; i < map->width+2; i++)
	{
		strcat(stageMapString, character[_OUT_OF_MAP_]);
	}
	strcat(stageMapString, "\n");
	for (i = 0; i < map->height; i++)
	{
		strcat(stageMapString, character[_OUT_OF_MAP_]);
		for (j = 0; j < map->width; j++)
		{
			switch (map->currMap[i][j])
			{
				case _NONE_:
		            strcat(stageMapString, character[_NONE_]);
					break;
				case _PLAYER_:
		            strcat(stageMapString, character[_NONE_]);
					break;
				case _WALL_:
		            strcat(stageMapString, character[_WALL_]);
					break;
				case _BALL_:
		            strcat(stageMapString, character[_BALL_]);
					break;
				case _EMPTY_BOX_:
		            strcat(stageMapString, character[_EMPTY_BOX_]);
					break;
				case _FILLED_BOX_:
		            strcat(stageMapString, character[_FILLED_BOX_]);
					break;
			}
		}
		strcat(stageMapString, character[_OUT_OF_MAP_]);
		strcat(stageMapString, "\n");
	}
	for (i = 0; i < map->width + 2; i++)
	{
		strcat(stageMapString, character[_OUT_OF_MAP_]);
	}
	strcat(stageMapString, "\n");

	/* Render stage map string to screen buffer. */
	setColor(bColor, tColor);
	renderString(stageMapString, centeredMapPos);
	renderPlayer(playerPos, bColor);

	/* Render Tooltip */
	// background
	stageMapString[0] = '\0';
	for (i = 0; i < 13; i++)
	{
		currIdx = i * (26 + 1);
		memset(stageMapString+currIdx, ' ', 26 * sizeof(char));
		stageMapString[currIdx+26] = '\n';
	}
	stageMapString[13*(26+1)] = '\0';
	setColor(bToolColor, tToolColor);
	renderString(stageMapString, tooltipPos);
	// text
	sprintf(tooltip[0], "[ HOW TO PLAY ]");
//	sprintf(tooltip[1], "E to Undo");
	sprintf(tooltip[1], "WASD or Arrow Keys");
	sprintf(tooltip[2], "R to Restart");
	sprintf(tooltip[3], "ESC to Pause");
	sprintf(tooltip[4], "Push %s into boxes!", character[_BALL_]);

	tooltipX = tooltipPos.X + 26;
	for (i = 0; i < 5; i++)
	{
		setColor(bToolColor, tToolColor);
		tooltipPos.X = (tooltipX - strlen(tooltip[i])) * 0.5 + 2;
		tooltipPos.Y += 2;
		renderString(tooltip[i], tooltipPos);
	}
	
	/* Render Movement */
	// background
	stageMapString[0] = '\0';
	for (i = 0; i < 4; i++)
	{
		currIdx = i * (20 + 1);
		memset(stageMapString+currIdx, ' ', 20 * sizeof(char));
		stageMapString[currIdx+20] = '\n';
	}
	stageMapString[4*(20+1)] = '\0';
	setColor(bToolColor, tToolColor);
	renderString(stageMapString, movementPos);
	// text
	sprintf(tooltip[0], "[ MOVEMENT ]");
	sprintf(tooltip[1], "  NOW : %3d ", movement);

	movementX = movementPos.X;
	for (i = 0; i <= 1; i++)
	{
		setColor(bToolColor, tToolColor);
		movementPos.X = movementX + (strlen(tooltip[i]) * 0.5) - 2;
		movementPos.Y += 1;
		renderString(tooltip[i], movementPos);
	}
}

void renderStageResultScreen(Ranking* ranking, const int stage, const int score, bool bLeftDown, bool bRightDown)
{
	ConsoleColor bColor = _SKYBLUE_, bBlankColor = _LIGHT_YELLOW_, tColor = _BLACK_, bStructColor = _DARK_PURPLE_, tStructColor = _GREEN_;
	COORD leftArrowPos = { _SCREEN_WIDTH_ * 0.04, _SCREEN_HEIGHT_ * 0.9 }, rightArrowPos = { _SCREEN_WIDTH_ * 0.86, _SCREEN_HEIGHT_ * 0.9 };
	COORD titlePos = { 0, _SCREEN_HEIGHT_ * 0.1 };
	COORD structurePos = { (_SCREEN_WIDTH_ - 80) * 0.5, (_SCREEN_HEIGHT_ - _MAP_HEIGHT_) * 0.5 + 2 };
	COORD halfPos, rankingPos = { _SCREEN_WIDTH_ * 0.3, _SCREEN_HEIGHT_ * 0.46 };
	DWORD dw;
	char leftArrowStr[16] = "◀ SAVE SCORE", rightArrowStr[16] = "NEXT STAGE ▶";
	char title[_SCREEN_WIDTH_ * 5], buffer[80*14+1];
	char halfScreen[(int)(_SCREEN_WIDTH_*0.6)*_SCREEN_HEIGHT_+1], *token;
	int i, j, currIdx, halfWidth = _SCREEN_WIDTH_ * 0.5, rankingX;

	fillColorToScreen(bColor, tColor);
	
	setColor(bBlankColor, tColor);
	for (i = 0; i < 20; i++)
	{
		currIdx = i * (80 + 1);
		memset(buffer + currIdx, ' ', 80 * sizeof(char));
		buffer[currIdx+80] = '\n';
	}
	buffer[(80+1)*20] = '\0';
	renderString(buffer, structurePos);

	setColor(bColor, tColor);
//	renderString(leftArrowStr, leftArrowPos);
	renderString(rightArrowStr, rightArrowPos);

	title[0] = '\0';
	sprintf(title, "%s┌────────────────────────────┐ \n", title);
	titlePos.X = (_SCREEN_WIDTH_ - (strlen(title) * 0.5)) * 0.6;
	sprintf(title, "%s│         LEADERBOARD        │ \n", title);
	sprintf(title, "%s└────────────────────────────┘ \n", title);
	renderString(title, titlePos);
	
	setColor(bBlankColor, tColor);
	title[0] = '\0';
	sprintf(title, "%s┌────────────────────┐ \n", title);
	titlePos.X = (_SCREEN_WIDTH_ - (strlen(title) * 0.5)) * 0.56;
	titlePos.Y += 5;
	sprintf(title, "%s│      STAGE %03d     │ \n", title, stage);
	sprintf(title, "%s└────────────────────┘ \n", title);
	renderString(title, titlePos);

	/* Print Ranking. */
	rankingPos.Y = _SCREEN_HEIGHT_ * 0.38;
	rankingPos.X = _SCREEN_WIDTH_ * 0.36;
	rankingX = rankingPos.X;
	
	for (i = 0; i < 10; i++)
	{
		switch (i)
		{
			case 0:
				setColor(bBlankColor, tColor);
				if (ranking[i].score < score) setColor(bBlankColor, _RED_);
				sprintf(buffer, "[ 1st ]");
				break;
			case 1:
				setColor(bBlankColor, tColor);
				sprintf(buffer, "[ 2nd ]");
				break;
			case 2:
				setColor(bBlankColor, tColor);
				sprintf(buffer, "[ 3rd ]");
				break;
			case 3:
				setColor(bBlankColor, tColor);
				sprintf(buffer, "[ 4th ]");
				break;
			case 4:
				setColor(bBlankColor, tColor);
				sprintf(buffer, "[ 5th ]");
				break;
			case 5:
				rankingPos.Y = _SCREEN_HEIGHT_ * 0.38;
				rankingPos.X = _SCREEN_WIDTH_ * 0.5;
				rankingX = rankingPos.X;
				setColor(bBlankColor, tColor);
				sprintf(buffer, "[ 6th ]");
				break;
			case 6:
				setColor(bBlankColor, tColor);
				sprintf(buffer, "[ 7th ]");
				break;
			case 7:
				setColor(bBlankColor, tColor);
				sprintf(buffer, "[ 8th ]");
				break;
			case 8:
				setColor(bBlankColor, tColor);
				sprintf(buffer, "[ 9th ]");
				break;
			case 9:
				setColor(bBlankColor, tColor);
				sprintf(buffer, "[ 10th ]");
				break;
				
		}
		rankingPos.X = rankingX + (rankingX - strlen(buffer)) * 0.5f;
		renderString(buffer, rankingPos);
		rankingPos.Y++;
		sprintf(buffer, "%s : %03d", ranking[i].name, ranking[i].score);
		rankingPos.X = rankingX + (rankingX - strlen(buffer)) * 0.5f;
		renderString(buffer, rankingPos);
		rankingPos.Y += 2;
	}
	setColor(bBlankColor, _RED_);
	rankingPos.Y = _SCREEN_HEIGHT_ * 0.56;
	rankingPos.X = _SCREEN_WIDTH_ * 0.22;
	rankingX = rankingPos.X;
	sprintf(buffer, "[ MY SCORE ]", score);
	rankingPos.X = rankingX + (rankingX - strlen(buffer)) * 0.5f;
	renderString(buffer, rankingPos);
	rankingPos.Y++;
	sprintf(buffer, "%03d", score);
	rankingPos.X = rankingX + (rankingX - strlen(buffer)) * 0.5f;
	renderString(buffer, rankingPos);
	if (score < ranking[0].score) 
	{
		rankingPos.Y++;
		sprintf(buffer, "(Best Score!!)");
		rankingPos.X = rankingX + (rankingX - strlen(buffer)) * 0.5f;
		renderString(buffer, rankingPos);
	}
	
	/* Fill color if arrow key down. */
	halfScreen[0] = '\0';
	if (bLeftDown || bRightDown)
	{
		for (i = 0; i < _SCREEN_HEIGHT_; i++)
		{
			currIdx = i * (halfWidth + 1);
			memset(halfScreen + currIdx, ' ', halfWidth * sizeof(char));
			halfScreen[currIdx+halfWidth] = '\n';
		}
		setColor(_YELLOW_, tColor);
		if (bLeftDown)
		{
			halfPos.X = 0;
			halfPos.Y = 0;
			renderString(halfScreen, halfPos);
		}
		else
		{
			halfPos.X = halfWidth;
			halfPos.Y = 0;
			renderString(halfScreen, halfPos);
		}
	}
}

void renderPauseScreen(int selectIndex)
{
	ConsoleColor bColor = _HOTPINK_, tColor = _DARK_PURPLE_, tTitleColor = _DARK_PURPLE_, tSelColor = _SKYBLUE_;
	const int MAX_SELECT = 5;
	COORD titlePos = { 0, (int)(_SCREEN_HEIGHT_ * 0.3) };
	COORD contentPos[MAX_SELECT], selectedPos;
	DWORD dw;
	char title[64], content[MAX_SELECT][64], selectedChar[5] = "▶ ";
	char bufferString[(_MAP_WIDTH_*2)*_MAP_HEIGHT_+1] = "";
	int i, contentPosY = _SCREEN_HEIGHT_ * 0.5;

	fillColorToScreen(bColor, tTitleColor);

	sprintf(title, "[ PAUSE MENU ]");
	titlePos.X = (_SCREEN_WIDTH_ - strlen(title)) * 0.5;

	i = 0;
	sprintf(content[i], "Continue");
	contentPos[i].X = (_SCREEN_WIDTH_ - strlen(content[i])) * 0.5;
	contentPos[i].Y = contentPosY;
	i++;
	sprintf(content[i], "Restart This Stage");
	contentPos[i].X = (_SCREEN_WIDTH_ - strlen(content[i])) * 0.5;
	contentPos[i].Y = contentPosY + i * 2;
	i++;
	sprintf(content[i], "Return to Stage Selection");
	contentPos[i].X = (_SCREEN_WIDTH_ - strlen(content[i])) * 0.5;
	contentPos[i].Y = contentPosY + i * 2;
	i++;
	sprintf(content[i], "Return to Main Menu");
	contentPos[i].X = (_SCREEN_WIDTH_ - strlen(content[i])) * 0.5;
	contentPos[i].Y = contentPosY + i * 2;
	i++;
	sprintf(content[i], "Exit Game");
	contentPos[i].X = (_SCREEN_WIDTH_ - strlen(content[i])) * 0.5;
	contentPos[i].Y = contentPosY + i * 2;
	i++;

	setColor(bColor, tColor);
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], titlePos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], title, strlen(title), &dw, NULL);
	for (i = 0; i < MAX_SELECT; i++)
	{
		if (i == selectIndex)
		{
			selectedPos.X = contentPos[i].X - 3;
			selectedPos.Y = contentPos[i].Y;
	        setColor(bColor, tSelColor);
		}
		else
		{
	        setColor(bColor, tColor);
		}
		SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], contentPos[i]);
		WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], content[i], strlen(content[i]), &dw, NULL);
	}
	setColor(bColor, tSelColor);
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], selectedPos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], selectedChar, strlen(selectedChar), &dw, NULL);
}

void renderSaveScreen(Ranking rank)
{
	ConsoleColor bColor = _DARK_PURPLE_, tColor = _WHITE_;
	COORD titlePos = { 0, (int)(_SCREEN_HEIGHT_ * 0.3) }, contentPos = { 0, (int)(_SCREEN_HEIGHT_ * 0.5) };
	COORD cursorPos;
	DWORD dw;
	char buffer[128];
	int i, j;

	fillColorToScreen(bColor, tColor);
	
	setColor(bColor, tColor);
	buffer[0] = '\0';
	sprintf(buffer, "%s┌────────────────────────────┐ \n", buffer);
	titlePos.X = (_SCREEN_WIDTH_ - (strlen(buffer) * 0.5)) * 0.6;
	sprintf(buffer, "%s│         SAVE SCORE         │ \n", buffer);
	sprintf(buffer, "%s└────────────────────────────┘ \n", buffer);
	renderString(buffer, titlePos);
	
	setColor(bColor, _BRIGHT_GRAY_);
	buffer[0] = '\0';
	sprintf(buffer, "SCORE : %03d", rank.score);
	contentPos.X = (int)((_SCREEN_WIDTH_ - strlen(buffer)) * 0.5);
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], contentPos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], buffer, strlen(buffer), &dw, NULL);
	contentPos.Y += 2;
	
	setColor(bColor, _YELLOW_);
	buffer[0] = '\0';
	strcpy(buffer, "NAME : ");
	strcat(buffer, rank.name);
	contentPos.X = (int)((_SCREEN_WIDTH_ - strlen(buffer)) * 0.5);
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], contentPos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], buffer, strlen(buffer), &dw, NULL);
	cursorPos.X = (int)((_SCREEN_WIDTH_ + strlen(buffer)) * 0.5);
	cursorPos.Y = 7 + contentPos.Y;
	contentPos.Y += 1;
	
	setColor(bColor, _BRIGHT_GRAY_);
	buffer[0] = '\0';
	sprintf(buffer, "(ALPHABET ONLY !)");
	contentPos.X = (int)((_SCREEN_WIDTH_ - strlen(buffer)) * 0.5);
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], contentPos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], buffer, strlen(buffer), &dw, NULL);
	
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], cursorPos);
}

void renderPlayer(COORD playerPos, ConsoleColor bColor)
{
	DWORD dw;
	setColor(bColor, _YELLOW_);
	SetConsoleCursorPosition(screenBuffer.buffer[screenBuffer.currentIndex], playerPos);
	WriteFile(screenBuffer.buffer[screenBuffer.currentIndex], character[_PLAYER_], strlen(character[_PLAYER_]), &dw, NULL);
}
