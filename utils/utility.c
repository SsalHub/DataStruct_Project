#define _CRT_SECURE_NO_WARNINGS
#include "utility.h"




/* pure utility func */
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoxyDetailed(int x, int y, int len)
{
	/* 좌표 대신 Align 값을 입력한 경우 */
	if (x < 1)
	{
		switch (x)
		{
			case _ALIGN_CENTER_:
				x = (_SCREEN_WIDTH_ - len) * 0.5f + 1;
				break;

			case _ALIGN_LEFT_:
				x = 1;
				break;

			case _ALIGN_RIGHT_:
				x = _SCREEN_WIDTH_;
				break;

			default:
				/* error */
				fprintf(stdout, "Error Occurred!\nx value in gotoxyWithLen(%d, %d, %d) func is invalid.\n", x, y, len);
				exit(1);
				break;
		}
	}
	if (y < 1)
	{
		switch (y)
		{
		case _ALIGN_CENTER_:
			y = _SCREEN_HEIGHT_ * 0.5f;
			break;

		case _ALIGN_TOP_:
			y = 1;
			break;

		case _ALIGN_BOTTOM_:
			y = _SCREEN_HEIGHT_;
			break;

		default:
			/* error */
			fprintf(stdout, "Error Occurred!\ny value in gotoxyWithLen(%d, %d, %d) func is invalid.\n", x, y, len);
			exit(1);
			break;
		}
	}

    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}




/* utility func of this game */
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

void clearScreen()
{
	int i, j;
	
	gotoxy(1, 1);
	for (j = 0; j < _SCREEN_HEIGHT_; j++)
	{
		for (i = 0; i < _SCREEN_WIDTH_; i++)
		{
			fprintf(stdout, " ");
		}
		fprintf(stdout, "\n");
	}
	gotoxy(1, 1);
}