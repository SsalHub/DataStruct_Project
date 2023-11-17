#define _CRT_SECURE_NO_WARNINGS
#include "utility.h"





/* utility func of this game */
void gotoxy(int x, int y)
{
	int convertX, convertY;
	convertX = convertXPos(x, 0);
	convertY = convertYPos(y, 0);

	if ((convertX < 1 || _SCREEN_WIDTH_ < convertX) || (convertY < 1 || _SCREEN_HEIGHT_ < convertY))
	{
		/* error */
		fprintf(stdout, "Error Occurred!\nx value in gotoxy(%d, %d) func is invalid.\n", x, y);
		exit(1);
	}

	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printString(char *s, int x, int y)
{
	char *token;
	int len, height, centerX, beginX, endX;

	/* First Line */
	token = strtok(s, "\n");
	len = strlen(token);
	height = getStringHeight(s);

	beginX = convertXPos(x, len);
	endX = beginX + len;

	y = convertYPos(y, height);
	centerX = beginX + (len * 0.5f);

	gotoxy(beginX, y++);
	fprintf(stdout, "%s\n", token);

	/* Second Line ~ Last Line */
	token = strtok(NULL, "\n");
	if (token == NULL) return;	// There is no second line 
	while (token != NULL)
	{
		len = strlen(token);
		beginX = centerX - (len * 0.5f);
		/* continue : error 발생, 문자열이 게임 테두리선을 넘어감 */ 
		if (beginX < 1) continue;
		gotoxy(beginX, y++);
		fprintf(stdout, "%s\n", token);
		token = strtok(NULL, "\n");
	}
}

void clearScreen()
{
	int i, j;

	for (j = 1; j <= _SCREEN_HEIGHT_; j++)
	{
		gotoxy(1, j);
		for (i = 0; i < _SCREEN_WIDTH_; i++)
		{
			fprintf(stdout, " ");
		}
	}
}








/* game initialization func*/
void initGame()
{
	drawBorder();
}

void drawBorder()
{
	int i, j;

	/* First Line*/
	for (i = 0; i < _SCREEN_WIDTH_ + 2; i++)
	{
		fprintf(stdout, "#");
	}
	fprintf(stdout, "\n");

	/* Middle Line */
	for (j = 0; j < _SCREEN_HEIGHT_; j++)
	{
		fprintf(stdout, "#");
		for (i = 0; i < _SCREEN_WIDTH_; i++)
		{
			fprintf(stdout, " ");
		}
		fprintf(stdout, "#\n");
	}

	/* Last Line */
	for (i = 0; i < _SCREEN_WIDTH_ + 2; i++)
	{
		fprintf(stdout, "#");
	}
	fprintf(stdout, "\n");
}








/* pure utility func */
int convertXPos(int x, int len)
{
	if (x < 1)
	{
		switch (x)
		{
		case _X_CENTER_:
			x = (_SCREEN_WIDTH_ - len) * 0.5f + 1;
			break;

		case _X_LEFT_:
			x = 1;
			break;

		case _X_RIGHT_:
			x = _SCREEN_WIDTH_;
			break;

		default:
			/* error */
			fprintf(stdout, "Error Occurred!\nx value in convertXPos(%d, %d) func is invalid.\n", x, len);
			exit(1);
			break;
		}
	}
	if (_SCREEN_WIDTH_ < x)
	{
		/* error */
		fprintf(stdout, "Error Occurred!\nx value in convertXPos(%d, %d) func is invalid.\n", x, len);
		exit(1);
	}
	return x;
}

int convertYPos(int y, int height)
{
	if (y < 1)
	{
		switch (y)
		{
		case _Y_CENTER_:
			y = (_SCREEN_HEIGHT_ - height) * 0.5f + 1;
			break;

		case _Y_TOP_:
			y = 1;
			break;

		case _Y_BOTTOM_:
			y = _SCREEN_HEIGHT_;
			break;

		default:
			/* error */
			fprintf(stdout, "Error Occurred!\ny value in convertYPos(%d, %d) func is invalid.\n", y, height);
			exit(1);
			break;
		}
	}
	if (_SCREEN_HEIGHT_ < y)
	{
		/* error */
		fprintf(stdout, "Error Occurred!\ny value in convertYPos(%d, %d) func is invalid.\n", y, height);
		exit(1);
	}
	return y;
}

int getStringHeight(char* s)
{
	char* p;
	int count = 1;

	p = s;
	while (*p != '\0')
	{
		if (*p == '\n') count++;
		p++;
	}
	return count;
}