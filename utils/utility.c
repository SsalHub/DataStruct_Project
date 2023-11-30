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
	wchar_t* ws;
	COORD pos;
	char* token;
	int len, width, height, beginX;
	
	len = strlen(s);
	if (len <= 0) return;

	width = height = 0;
	ws = (wchar_t*)malloc(sizeof(wchar_t)*len + 1);
	MultiByteToWideChar(CP_ACP, 0, s, len + 1, ws, MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, NULL));
	setStringInfo(ws, &width, &height);
	free(ws);
	if (width % 2 != 0) width++;

	/* Fix X Coordinate */
	if (x < 1)
	{
		switch (x)
		{
		case _ALIGN_CENTER_:
			beginX = ((_BORDER_RIGHT_ - 1) - width) * 0.5f;
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








/* game initialization func*/
void initGame()
{
	_wsetlocale(LC_ALL, L"Korean");
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








/* pure utility func */
void setStringInfo(wchar_t* ws, int* w, int* h)
{
	wchar_t *token, *wp = NULL;
	int len;

	token = wcstok(ws, L"\n", &wp);
	while (token)
	{
		*h += 1;
		len = wcwidth(token);
		if (*w < len) *w = len;
		token = wcstok(NULL, L"\n", &wp);
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

// https://github.com/mattn/wcwidth.c/blob/master/wcwidth.c
static int bisearch(wchar_t ucs, const struct interval* table, int max) {
	int min = 0;
	int mid;

	if (ucs < table[0].first || ucs > table[max].last)
		return 0;
	while (max >= min) {
		mid = (min + max) / 2;
		if (ucs > table[mid].last)
			min = mid + 1;
		else if (ucs < table[mid].first)
			max = mid - 1;
		else
			return 1;
	}

	return 0;
}

// https://github.com/mattn/wcwidth.c/blob/master/wcwidth.c
int wcwidth(wchar_t ucs) {
	/* sorted list of non-overlapping intervals of non-spacing characters */
	static const struct interval combining[] = {
	  { 0x0300, 0x034E }, { 0x0360, 0x0362 }, { 0x0483, 0x0486 },
	  { 0x0488, 0x0489 }, { 0x0591, 0x05A1 }, { 0x05A3, 0x05B9 },
	  { 0x05BB, 0x05BD }, { 0x05BF, 0x05BF }, { 0x05C1, 0x05C2 },
	  { 0x05C4, 0x05C4 }, { 0x064B, 0x0655 }, { 0x0670, 0x0670 },
	  { 0x06D6, 0x06E4 }, { 0x06E7, 0x06E8 }, { 0x06EA, 0x06ED },
	  { 0x070F, 0x070F }, { 0x0711, 0x0711 }, { 0x0730, 0x074A },
	  { 0x07A6, 0x07B0 }, { 0x0901, 0x0902 }, { 0x093C, 0x093C },
	  { 0x0941, 0x0948 }, { 0x094D, 0x094D }, { 0x0951, 0x0954 },
	  { 0x0962, 0x0963 }, { 0x0981, 0x0981 }, { 0x09BC, 0x09BC },
	  { 0x09C1, 0x09C4 }, { 0x09CD, 0x09CD }, { 0x09E2, 0x09E3 },
	  { 0x0A02, 0x0A02 }, { 0x0A3C, 0x0A3C }, { 0x0A41, 0x0A42 },
	  { 0x0A47, 0x0A48 }, { 0x0A4B, 0x0A4D }, { 0x0A70, 0x0A71 },
	  { 0x0A81, 0x0A82 }, { 0x0ABC, 0x0ABC }, { 0x0AC1, 0x0AC5 },
	  { 0x0AC7, 0x0AC8 }, { 0x0ACD, 0x0ACD }, { 0x0B01, 0x0B01 },
	  { 0x0B3C, 0x0B3C }, { 0x0B3F, 0x0B3F }, { 0x0B41, 0x0B43 },
	  { 0x0B4D, 0x0B4D }, { 0x0B56, 0x0B56 }, { 0x0B82, 0x0B82 },
	  { 0x0BC0, 0x0BC0 }, { 0x0BCD, 0x0BCD }, { 0x0C3E, 0x0C40 },
	  { 0x0C46, 0x0C48 }, { 0x0C4A, 0x0C4D }, { 0x0C55, 0x0C56 },
	  { 0x0CBF, 0x0CBF }, { 0x0CC6, 0x0CC6 }, { 0x0CCC, 0x0CCD },
	  { 0x0D41, 0x0D43 }, { 0x0D4D, 0x0D4D }, { 0x0DCA, 0x0DCA },
	  { 0x0DD2, 0x0DD4 }, { 0x0DD6, 0x0DD6 }, { 0x0E31, 0x0E31 },
	  { 0x0E34, 0x0E3A }, { 0x0E47, 0x0E4E }, { 0x0EB1, 0x0EB1 },
	  { 0x0EB4, 0x0EB9 }, { 0x0EBB, 0x0EBC }, { 0x0EC8, 0x0ECD },
	  { 0x0F18, 0x0F19 }, { 0x0F35, 0x0F35 }, { 0x0F37, 0x0F37 },
	  { 0x0F39, 0x0F39 }, { 0x0F71, 0x0F7E }, { 0x0F80, 0x0F84 },
	  { 0x0F86, 0x0F87 }, { 0x0F90, 0x0F97 }, { 0x0F99, 0x0FBC },
	  { 0x0FC6, 0x0FC6 }, { 0x102D, 0x1030 }, { 0x1032, 0x1032 },
	  { 0x1036, 0x1037 }, { 0x1039, 0x1039 }, { 0x1058, 0x1059 },
	  { 0x1160, 0x11FF }, { 0x17B7, 0x17BD }, { 0x17C6, 0x17C6 },
	  { 0x17C9, 0x17D3 }, { 0x180B, 0x180E }, { 0x18A9, 0x18A9 },
	  { 0x200B, 0x200F }, { 0x202A, 0x202E }, { 0x206A, 0x206F },
	  { 0x20D0, 0x20E3 }, { 0x302A, 0x302F }, { 0x3099, 0x309A },
	  { 0xFB1E, 0xFB1E }, { 0xFE20, 0xFE23 }, { 0xFEFF, 0xFEFF },
	  { 0xFFF9, 0xFFFB }
	};

	/* test for 8-bit control characters */
	if (ucs == 0)
		return 0;
	if (ucs < 32 || (ucs >= 0x7f && ucs < 0xa0))
		return -1;

	/* binary search in table of non-spacing characters */
	if (bisearch(ucs, combining,
		sizeof(combining) / sizeof(struct interval) - 1))
		return 0;

	/* if we arrive here, ucs is not a combining or C0/C1 control character */

	return 1 +
		(ucs >= 0x1100 &&
			(ucs <= 0x115f ||                    /* Hangul Jamo init. consonants */
				(ucs >= 0x2e80 && ucs <= 0xa4cf && (ucs & ~0x0011) != 0x300a &&
					ucs != 0x303f) ||                  /* CJK ... Yi */
				(ucs >= 0xac00 && ucs <= 0xd7a3) || /* Hangul Syllables */
				(ucs >= 0xf900 && ucs <= 0xfaff) || /* CJK Compatibility Ideographs */
				(ucs >= 0xfe30 && ucs <= 0xfe6f) || /* CJK Compatibility Forms */
				(ucs >= 0xff00 && ucs <= 0xff5f) || /* Fullwidth Forms */
				(ucs >= 0xffe0 && ucs <= 0xffe6) ||
				(ucs >= 0x20000 && ucs <= 0x2ffff)
				));
}