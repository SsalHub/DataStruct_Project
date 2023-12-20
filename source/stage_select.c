#define _CRT_SECURE_NO_WARNINGS
#include "stage_select.h"

void loadStageSelect()
{
	int stage = 1;
	char fname[64], *map;

	loadMapData(map, stage);

	free(map);
}

void loadMapData(char* dst, const int stage)
{
	char fname[64], *buffer;
	long fsize;
	FILE* fp;
	sprintf(fname, "%s/Stage%02d.skb", MAP_PATH, stage);
	fp = fopen(fname, "r");
	if (fp == NULL) exit(1);

	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET); 
	buffer = (char*)malloc(sizeof(char) * (fsize + 1));
	fread(buffer, fsize, 1, fp);

	dst = buffer;
}