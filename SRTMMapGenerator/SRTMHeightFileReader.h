#pragma once

const int SRTM_POTENTIONAL_MAXIMUM_EARTH_HEIGHT = 9000;
const int SRTM_DATA_RESOLUTION = 90;
const int SRTM_SIMULATION_GRANITY = 1;
const int SRTM_TILE_WIDTH = 1201;
const int SRTM_TILE_HEIGHT = 1201;
const int SRTM_TILE_DEPTH = ((SRTM_POTENTIONAL_MAXIMUM_EARTH_HEIGHT / SRTM_DATA_RESOLUTION) * SRTM_SIMULATION_GRANITY);

#include <string>
#include <climits>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

class SRTMHeightFileReader
{
public:
	SRTMHeightFileReader();
	~SRTMHeightFileReader();

	short ** readHRTFileIntoBuffer(string file);
};

