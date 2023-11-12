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
