#include "BaseData.h"

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

void gotoxy(char* s, int xAlign, int yAlign)
{
	int x, y;
	switch (xAlign)
	{
		case _CENTER_:
			x = (_SCREEN_WIDTH_ - strlen(s)) * 0.5f + 1;
			break;

		case _LEFT_:
			x = 1;
			break;

		case _RIGHT_:
			x = _SCREEN_WIDTH_ - 1;
			break;

		default:
			x = 1;
			break;
	}

	switch (yAlign)
	{
		case _CENTER_:
			y = _SCREEN_HEIGHT_ * 0.5f;
			break;

		case _UP_:
			y = 1;
			break;

		case _DOWN_:
			y = _SCREEN_HEIGHT_ - 1;
			break;

		default:
			y = 1;
			break;
	}

	gotoxy(x, y);
}