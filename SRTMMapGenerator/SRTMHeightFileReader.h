#pragma once


#include <string>
#include <climits>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "SRTMConstants.h"

using namespace std;

struct SRTMHeightFileDescriptor {
	short ** heights;
	short lowestPoint;
	short highestPoint;
};

class SRTMHeightFileReader
{
public:
	SRTMHeightFileReader();
	~SRTMHeightFileReader();

	SRTMHeightFileDescriptor readHRTFileIntoBuffer(string file);
};

