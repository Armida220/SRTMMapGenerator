#pragma once

#include <algorithm> 
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

class SRTMStatisticsMethods
{
public:
	SRTMStatisticsMethods();
	~SRTMStatisticsMethods();

	vector<short> checkForOutliersUsingIQR(vector<short> values);
	float getMedianForVector(vector<short> v);
};

