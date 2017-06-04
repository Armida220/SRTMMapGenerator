#include "stdafx.h"
#include "SRTMHeightFileReader.h"


SRTMHeightFileReader::SRTMHeightFileReader()
{
}


SRTMHeightFileReader::~SRTMHeightFileReader()
{
}


short ** SRTMHeightFileReader::readHRTFileIntoBuffer(string file)
{
	short** heights = new short*[SRTM_TILE_WIDTH];
	short lowestPoint = SHRT_MAX;
	short highestPoint = SHRT_MIN;

	#pragma warning (disable : 4996)
	FILE *f = fopen(file.c_str(), "rb");

	unsigned char buff[2];
	for (int h = 0; h < SRTM_TILE_HEIGHT ; h++) {
		heights[h] = new short[SRTM_TILE_WIDTH];
		for (int w = 0; w < SRTM_TILE_WIDTH; w++) {
			int read = fread(buff, sizeof(unsigned char), sizeof(buff), f);
			heights[h][w] = (buff[0] << 8) | buff[1];

			if (lowestPoint > heights[h][w]) {
				lowestPoint = heights[h][w];
			}

			if (highestPoint < heights[h][w])
			{
				highestPoint = heights[h][w];
			}
		}
	}

	fclose(f);
	return heights;
}