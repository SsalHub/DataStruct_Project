#ifndef __BASEDATA__
#define __BASEDATA__

#define _SCREEN_WIDTH_	60
#define _SCREEN_HEIGHT_	24

#define _CENTER_	0
#define _LEFT_		1
#define _RIGHT_		2
#define _UP_		3
#define _DOWN_		4

#include "../utils/UtilData.h"

#include <string.h>

void initGame();
void drawBorder();
void gotoxy(char* s, int xAlign, int yAlign);

#endif