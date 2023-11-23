#define _CRT_SECURE_NO_WARNINGS
#include "utility.h"





/* utility func of this game */
void gotoxy(int x, int y)
{
	COORD pos = { x, y };

	if (x < 1)
	{
		switch (x)
		{
		case _ALIGN_CENTER_:
			pos.X = (_BORDER_RIGHT_ - 1) * 0.5f;
			break;

		case _ALIGN_LEFT_:
			pos.X = _BORDER_LEFT_;
			break;

		case _ALIGN_RIGHT_:
			pos.X = _BORDER_RIGHT_ - 1;
			break;

		default:
			/* error case */
			pos.X = _BORDER_LEFT_;
		}
	}
	else
	{
		if (_BORDER_RIGHT_ <= x)
			/* error case */
			pos.X = _BORDER_RIGHT_ - 1;
	}

	if (y < 1)
	{
		switch (y)
		{
		case _ALIGN_CENTER_:
			pos.Y = (_BORDER_BOTTOM_ - 1) * 0.5f;
			break;

		case _ALIGN_TOP_:
			pos.Y = _BORDER_TOP_;
			break;

		case _ALIGN_BOTTOM_:
			pos.Y = _BORDER_BOTTOM_ - 1;
			break;

			/* error case */
		default:
			pos.Y = _BORDER_TOP_;
		}
	}
	else
	{
		/* error case */
		if (_BORDER_BOTTOM_ <= y)
			pos.Y = _BORDER_BOTTOM_ - 1;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printString(char* s, int x, int y)
{
	COORD pos;
	char* token;
	int len, width, height, beginX;
	
	len = strlen(s);
	if (len <= 0) return;

	setStringInfo(s, &width, &height);
	if (width % 2 != 0) width++;

	/* Fix X Coordinate */
	if (x < 1)
	{
		switch (x)
		{
		case _ALIGN_CENTER_:
			beginX = ((_SCREEN_WIDTH_ - 1) - width) * 0.5f;
			break;

		case _ALIGN_LEFT_:
			beginX = _BORDER_LEFT_ + 1;
			break;

		case _ALIGN_RIGHT_:
			beginX = (_BORDER_RIGHT_ - 1) - width;
			break;

		default:
			/* error case */
			beginX = _BORDER_LEFT_ + 1;
		}
	}
	else
	{
		/* error case */
		if (_BORDER_RIGHT_ <= x)
			beginX = (_BORDER_RIGHT_ - 1) - width;
		else
			beginX = x;
	}
	/* Fix Y Coordinate */
	if (y < 1)
	{
		switch (y)
		{
		case _ALIGN_CENTER_:
			pos.Y = (_SCREEN_HEIGHT_ - height) * 0.5f;
			break;

		case _ALIGN_TOP_:
			pos.Y = _BORDER_TOP_ + 1;
			break;

		case _ALIGN_BOTTOM_:
			pos.Y = (_BORDER_BOTTOM_ - 1) - height;
			break;

		default:
			/* error case */
			pos.Y = _BORDER_TOP_ + 1;
		}
	}
	else
	{
		/* error case */
		if (_BORDER_BOTTOM_ <= y)
			pos.Y = (_BORDER_BOTTOM_ - 1) - height;
		else
			pos.Y = y;
	}
	/* Main Loop */
	token = strtok(s, "\n");
	while (token != NULL)
	{
		if (_BORDER_BOTTOM_ <= pos.Y) return;
		if (pos.Y <= _BORDER_TOP_)
		{
			token = strtok(NULL, "\n");
			pos.Y++;
			continue;
		}
		// else
		pos.X = beginX;
		fixEachLine(token, &(pos.X));

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		fprintf(stdout, token);

		token = strtok(NULL, "\n");
		pos.Y++;
	}
}

void clearScreen()
{
	COORD pos = { _BORDER_LEFT_ + 1, 0 };
	int i, j;

	for (j = _BORDER_TOP_ + 1; j < _BORDER_BOTTOM_; j++)
	{
		pos.Y = j;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		for (i = 0; i < _SCREEN_WIDTH_; i++)
		{
			fprintf(stdout, " ");
		}
	}
}







/* pure utility func */
void setStringInfo(char* s, int* w, int* h)
{
	char* p;
	int len;

	*w = 0;
	*h = 1;
	len = 0;
	p = s;
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			if (*w < len) *w = len;
			len = 0;
			*h += 1;
			p++;
			continue;
		}
		// else
		len++;
		p++;
	}
}

void fixEachLine(char* currStr, short* x)
{
	char* nextStr;
	int len, exclude, endX;

	len = strlen(currStr);

	/* Fix Begin Index(coordinate) into Game Area */
	if (*x <= _BORDER_LEFT_)
	{
		exclude = (_BORDER_LEFT_ + 1) - *x;
		len -= exclude;
		currStr += exclude;
		*x = 1;
	}
	/* Insert NULL Character to Exclude Off-Screen Characters from Original String */
	endX = *x + len;
	if (_BORDER_RIGHT_ <= endX)
	{
		nextStr = currStr + len + 1;
		exclude = (endX - (_BORDER_RIGHT_ - 1));
		len -= exclude;
		*(currStr + len) = '\n';
		*(currStr + len + 1) = '\0';
		/* Append Each Separated String, 'currStr' and 'nextStr' */
		strcat(currStr, nextStr);
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
	for (i = 0; i < _BORDER_RIGHT_; i++)
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
	for (i = 0; i < _BORDER_RIGHT_; i++)
	{
		fprintf(stdout, "#");
	}
	fprintf(stdout, "\n");
}



