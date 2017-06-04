#include "stdafx.h"
#include "SRTMStatisticsMethods.h"


SRTMStatisticsMethods::SRTMStatisticsMethods()
{
}

SRTMStatisticsMethods::~SRTMStatisticsMethods()
{
}

vector<short> SRTMStatisticsMethods::checkForOutliersUsingIQR(vector<short> originalValues)
{
	vector<short> values(originalValues.begin(), originalValues.end());
	sort(values.begin(), values.end());

	float Q1 = ((values.size() & 1) == 0) ?
		getMedianForVector(vector<short>(values.begin(), values.begin() + (values.size() / 2))) :
		getMedianForVector(vector<short>(values.begin(), values.begin() + ceil(values.size() / 2)));

	float Q2 = getMedianForVector(values);
	
	float Q3 = ((values.size() & 1) == 0) ?
		getMedianForVector(vector<short>(values.begin() + (values.size() / 2), values.end())) :
		getMedianForVector(vector<short>(values.begin() + ceil(values.size() / 2), values.end()));

	float IQR = Q3 - Q1;
	float lowLimit = Q1 - (1.5 * IQR);
	float highLimit = Q3 + (1.5 * IQR);

	vector<short> outliers;

	for (short value : values) {
		if (value < lowLimit) {
			outliers.insert(outliers.end(), value);
		} else if (value > highLimit) {
			outliers.insert(outliers.end(), value);
		}
	}

	return outliers;
}

float SRTMStatisticsMethods::getMedianForVector(vector<short> v)
{
	if ((v.size() & 1) == 0)
	{
		return (float) (((float) v.at((v.size() / 2)) + (float) v.at((v.size() / 2) - 1)) / 2);
	} else {
		return v.at(ceil(v.size() / 2));
	}
}