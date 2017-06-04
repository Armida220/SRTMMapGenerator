#include "stdafx.h"
#include "SRTMFileDescriptor.h"


SRTMFileDescriptor::SRTMFileDescriptor()
{
}


SRTMFileDescriptor::~SRTMFileDescriptor()
{
}

bool SRTMFileDescriptor::fillFromMatchingGroups(boost::match_results<std::string::const_iterator> matchingGroups)
{
	parentFolder = matchingGroups[PARENT_FOLDER_MATCHING_INDEX];
	latitudeDirection = matchingGroups[LATITUDE_DIRECTION_MATCHING_INDEX];
	latitude = matchingGroups[LATITUDE_MATCHING_INDEX];
	longtitudeDirection = matchingGroups[LONGTITUDE_DIRECTION_MATCHING_INDEX];
	longtitude = matchingGroups[LONGTITUDE_MATCHING_INDEX];
	afterContent = matchingGroups[AFTER_CONTENT_MATCHING_INDEX];

	return true;
}

string SRTMFileDescriptor::unzippedFile()
{
	string unzippedFile;
	unzippedFile.append(latitudeDirection);
	unzippedFile.append(latitude);
	unzippedFile.append(longtitudeDirection);
	unzippedFile.append(longtitude);
	unzippedFile.append(".hgt");
	return unzippedFile;
}

string SRTMFileDescriptor::unzippedPath()
{
	string unzippedPath;
	unzippedPath.append(parentFolder);
	unzippedPath.append(unzippedFile());
	return unzippedPath;
}



