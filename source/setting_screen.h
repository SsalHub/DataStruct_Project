#ifndef __SETTINGSCREEN__
#define __SETTINGSCREEN__

#include "../utils/utility.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

extern int volume;

void ShowSettings();
void AdjustVolume();
void SelectLevel(int Level);

#endif