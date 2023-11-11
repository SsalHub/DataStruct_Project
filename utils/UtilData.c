#include "UtilData.h"

void gotoxy(int x, int y)
{
    #ifdef _WIN32
    COORD pos = { x, y };
    SetConsoleCursorPosition(stdout, pos);  // windows.h
    #else
    fprintf(stdout, "\033[%d;%df", y, x);
	fflush(stdout);
    #endif
}

void waitForSeconds(float s)
{
    #ifdef _WIN32
    Sleep(s * 1000);    // windows.h
    #else
    sleep(s);           // unistd.h
    #endif
}

int onKeyboardInput()
{
    #ifdef _WIN32
    return _kbhit();
    #else
    unsigned char ch;
    int nread;

    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0, &ch, 1);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
    if (nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
    #endif
}

char getChar()
{
    #ifdef _WIN32
    return _getch();     // conio.h
    # else
    char ch;

    if (peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0, &ch, 1);
    return ch;
    # endif
}