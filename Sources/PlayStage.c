#include "../Headers/PlayStage.h"

void playStage()
{
	MapDataDLL* pMapDLL;
	Flag flag;
	char s[16];
	int stageIndex = 1, score;
	
	flag = _STAGE_SELECT_;
	while(1)
	{
		if (flag == _STAGE_SELECT_)
			stageIndex = loadStageSelect(stageIndex);
		
//		_beginthreadex(NULL, 0, printStageLoadingScreen, (void*)&bPaused, 0, NULL);
		sprintf(s, "Stage %03d", stageIndex);
		printStageLoadingScreen(s);
		pMapDLL = findMapDataDLL(stageIndex);
		
		flag = playGame(&(pMapDLL->mapData), &score);
		
		switch (flag)
		{
			case _STAGE_CLEAR_:
				stageClear(stageIndex);
				showResultScreen(stageIndex, score);
				if (stageIndex < maxStage)
					stageIndex++;
				else
					YouWonThisGame();
				break;
				
			case _MAIN_MENU_:
				sprintf(s, "Main Menu");
				printStageLoadingScreen(s);
				return;
				
			case _EXIT_GAME_:
				exitGame();
				
			case _STAGE_SELECT_:
			case _STAGE_RESTART_:
			default:
				break;
		}
	}
}

int loadStageSelect(int stageIndex)
{
	Flag flag;
	MapDataDLL* pMapDLL;
	char input;
	
	pMapDLL = findMapDataDLL(stageIndex);		// stageIndex = 1
	
	printStageSelectScreen(&(pMapDLL->mapData), maxStage, false, false);
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
				case _ESCAPE_:
				case _LEFT_:
					if (1 < pMapDLL->mapData.stageIndex)
						pMapDLL = pMapDLL->before;
					printStageSelectScreen(&(pMapDLL->mapData), maxStage, true, false);
					WaitForSeconds(0.1);
					printStageSelectScreen(&(pMapDLL->mapData), maxStage, false, false);
					WaitForSeconds(0.1);
					break;
				case _RIGHT_:
					if (pMapDLL->mapData.stageIndex < maxStage)
						pMapDLL = pMapDLL->after;
					printStageSelectScreen(&(pMapDLL->mapData), maxStage, false, true);
					WaitForSeconds(0.1);
					printStageSelectScreen(&(pMapDLL->mapData), maxStage, false, false);
					WaitForSeconds(0.1);
					break;
				case _SPACE_:
				case _CARRIGE_RETURN_:
					/* select ok */
					return pMapDLL->mapData.stageIndex;
				default:
					break;
			}
		}
	}
}

Flag playGame(MapData* pMap, int* score)
{
	Flag flag;
	MapData map;
	char input;
	int selectIndex, movement;
	
	flag = _FALSE_;
	copyMapData(&map, pMap);
	setPlayerPos(&map, map.playerBeginPos.X, map.playerBeginPos.Y);
	map.currentMove = 0;
	movement = 0;
	
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
				case _UPPER_A_:
				case _LOWER_A_:
				case _LEFT_:
					flag = translatePlayerPos(&map, -1, 0);
					movement++;
					break;
				case _UPPER_D_:
				case _LOWER_D_:
				case _RIGHT_:
					flag = translatePlayerPos(&map, 1, 0);
					movement++;
					break;
				case _UPPER_W_:
				case _LOWER_W_:
				case _UP_:
					flag = translatePlayerPos(&map, 0, -1);
					movement++;
					break;
				case _UPPER_S_:
				case _LOWER_S_:
				case _DOWN_:
					flag = translatePlayerPos(&map, 0, 1);
					movement++;
					break;
					
//				case _UPPER_E_:
//				case _LOWER_E_:
//					flag = undoPlayerAction(&map);
//					if (0 < movement) movement--;
//					break;
				case _UPPER_R_:
				case _LOWER_R_:
					flag = confirmRestartStage();
					break;
					
				case _ESCAPE_:
					selectIndex = pauseGame();
					switch (selectIndex)
					{
						case 0:		// continue
							break;
						case 1:		// restart
							flag = _STAGE_RESTART_;
							break;
						case 2:		// return to stage selection
							flag = _STAGE_SELECT_;
							break;
						case 3:		// return to main menu
							flag = _MAIN_MENU_;
							break;
						case 4:		// exit game
							flag = _EXIT_GAME_;
							break;
					}
					break;
					
				case _SPACE_:
				default:
					break;
			}
		}
		
		switch (flag)
		{
			case _MAIN_MENU_:
			case _STAGE_SELECT_:
			case _STAGE_RESTART_:
			case _EXIT_GAME_:
				return flag;
				
			case _STAGE_CLEAR_:
				printStageMapScreen(&map, movement);
				*score = movement;
				return flag;
				
			default:	// continue while loop
				break;	
		}
		printStageMapScreen(&map, movement);
	}
}

Flag confirmRestartStage()
{
	char input;
	
	printScreen(renderConfirmRestartScreen);
	
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
				case _ESCAPE_:
				case _LEFT_:
					return _FALSE_;
				case _RIGHT_:
					return _STAGE_RESTART_;
			}
		}
	}
}

int pauseGame()
{
	const int MAX_SELECT = 5;
	int selectIndex = 0;
	char input;
	
	printPauseScreen(selectIndex);
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
				case _DOWN_:
					if (selectIndex + 1 < MAX_SELECT)
						selectIndex += 1;
					
					printPauseScreen(selectIndex);
					WaitForSeconds(0.1);
					break;
				case _UP_:
					if (0 <= selectIndex - 1)
						selectIndex -= 1;
						
					printPauseScreen(selectIndex);
					WaitForSeconds(0.1);
					break;
				case _SPACE_:
				case _CARRIGE_RETURN_:
					/* select ok */
					return selectIndex;
				default:
					break;
			}
		}
	}
}

void stageClear(int stageIndex)
{
	MapDataDLL* pMapDLL;
	
	pMapDLL = findMapDataDLL(stageIndex);
	
	releasePlayerHistory(&(pMapDLL->mapData));
	printStageClearScreen(stageIndex);
}

void showResultScreen(const int stage, const int score)
{
	Ranking ranking[10];
	char i, input, leaderboard[1001], *token, buffer[32], *bufToken;
	
	getLeaderboard(leaderboard, stage);
	
	token = strtok(leaderboard, "\n");
	for (i = 0; i < 10; i++)
	{
		if (token == NULL)
		{
			ranking[i].score = 0;
			strcpy(ranking[i].name, "---");
			continue;
		}
		strcpy(buffer, token);
		bufToken = buffer;
		while (*bufToken != ' ')
		{
			bufToken++;
		}
		*(bufToken++) = '\0';
		ranking[i].score = atoi(buffer);
		strcpy(ranking[i].name, bufToken);
		
		token = strtok(NULL, "\n");
	}
	printStageResultScreen(ranking, stage, score, false, false);
	
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
				/* SAVE */
//				case _LEFT_:
//				case _UPPER_A_:
//				case _LOWER_A_:
//					printStageResultScreen(ranking, stage, score, true, false);
//					WaitForSeconds(0.1);
//					printStageResultScreen(ranking, stage, score, false, false);
//					showSaveScreen(ranking, stage, score);
//					break;
					
				/* NEXT STAGE */
				case _RIGHT_:
				case _UPPER_D_:
				case _LOWER_D_:
				case _CARRIGE_RETURN_:
					printStageResultScreen(ranking, stage, score, false, true);
					WaitForSeconds(0.1);
					printStageResultScreen(ranking, stage, score, false, false);
					return;
			}
		}
	}
}

void showSaveScreen(Ranking* ranking, const int stage, const int score)
{
	Ranking newRank;
	CONSOLE_CURSOR_INFO cursor;
	char input;
	
	cursor.dwSize = 1;
	cursor.bVisible = true;
	SetConsoleCursorInfo(screenBuffer.buffer[screenBuffer.currentIndex], &cursor);
	
	newRank.score = score;
	strcpy(newRank.name, "");
	printSaveScreen(newRank);
	
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			if (97 <= input && input <= 122)
			{
				input -= 32;
			}
			if (65 <= input && input <= 90)
			{
				newRank.name[strlen(newRank.name)] = input;
				newRank.name[strlen(newRank.name)+1] = '\0';
				printSaveScreen(newRank);
				continue;
			}
			else if (input == _BACKSPACE_)
			{
				newRank.name[strlen(newRank.name)-1] = '\0';
				printSaveScreen(newRank);
				continue;
			}
			else if (input == _CARRIGE_RETURN_)
			{
				break;
			}
			else 
			{
				showRedEffect(); 
				WaitForSeconds(0.1);
				printSaveScreen(newRank);
			}
		}
	}
	
	cursor.bVisible = false;
	SetConsoleCursorInfo(screenBuffer.buffer[screenBuffer.currentIndex], &cursor);
}
