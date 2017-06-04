#pragma once

#define PARENT_FOLDER_MATCHING_INDEX 1
#define LATITUDE_DIRECTION_MATCHING_INDEX 2
#define LATITUDE_MATCHING_INDEX 3
#define LONGTITUDE_DIRECTION_MATCHING_INDEX 4
#define LONGTITUDE_MATCHING_INDEX 5
#define AFTER_CONTENT_MATCHING_INDEX 6


#include <string>
#include <boost/range/iterator_range.hpp>	
#include <boost/regex.hpp>

using namespace std;

class SRTMFileDescriptor
{
public:
	SRTMFileDescriptor();
	~SRTMFileDescriptor();

	string parentFolder;
	string latitudeDirection;
	string latitude;
	string longtitudeDirection;
	string longtitude;
	string afterContent;

	bool fillFromMatchingGroups(boost::match_results<std::string::const_iterator>);
	string unzippedFile();
	string unzippedPath();
};

