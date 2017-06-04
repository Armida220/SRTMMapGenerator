// SRTMMapGenerator.cpp : Defines the entry point for the console application.
// Author: Dan Novák (Hawuawu@gmail.com)
// SRTM Data usage https://dds.cr.usgs.gov/srtm/version1/Documentation/SRTM_Topo.txt
// Iterating over directory using boost http://www.boost.org/doc/libs/1_57_0/libs/filesystem/example/tut3.cpp
//

#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>	
#include <boost/regex.hpp>

#include <zip.h>

#include "SRTMZipDecompressor.h"
#include "SRTMFileDescriptor.h"
#include "SRTMHeightFileReader.h"
#include "SRTMStatisticsMethods.h"

using namespace std;

int main(int argc, const char * argv[])
{

	bool agregatingIntoOneMapFile = false;
	bool usingZip = false;

	boost::filesystem::path p(argc > 1 ? argv[1] : ".");
	for (int i = 2; i < argc; i++) {
		if (string(argv[i]) == "-agregate") {
			agregatingIntoOneMapFile = true;
		} if (string(argv[i]) == "-zip") {
			usingZip = true;
		}
		else if (string(argv[i]) == "-?" || string(argv[i]) == "?") {
			cout << "Usage of SRTMMapGenerator:\n";
			cout << "Basic usage................................. SRTMGenerator.exe c:\\path\\to\\srtm\\folder\n";
			cout << "Agregate map files into one map ............ SRTMGenerator.exe c:\\path\\to\\srtm\\folder -agregate\n";
			cout << "Height data are in zip file, decompresing... SRTMGenerator.exe c:\\path\\to\\srtm\\folder -zip\n";
			return 0;
		}
	}

	string generalPattern = "(.*)([NSns])([0-9]+)([EWew])([0-9]+)(.*)\\.hgt$";
	string generalPatternWithZip = "(.*)([NSns])([0-9]+)([EWew])([0-9]+)(.*)\\.hgt\\.zip$";

	cout << "Checking folder for files matching regex patterns: ";
	cout << ((usingZip) ? "" : "....") << " " << generalPattern << "\n";

	boost::regex generalRegex(generalPattern);
	boost::regex generalRegexUsingZip(generalPatternWithZip);

	try
	{
		if (boost::filesystem::exists(p))
		{

			if (boost::filesystem::is_directory(p)) {
				for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {})) {
					
					string path = entry.path().string();
					SRTMFileDescriptor descriptor;
					bool matchingDescriptor = false;

					if (usingZip) {
						boost::match_results<std::string::const_iterator> matchingGroups;
						if (boost::regex_match(path, matchingGroups, generalRegexUsingZip))
						{

							matchingDescriptor = descriptor.fillFromMatchingGroups(matchingGroups);

							cout << "\n===== Reading file: " << path << " ===== \n";
							cout << "For tile with coordinates: " << descriptor.latitude << descriptor.latitudeDirection;
							cout << " and " << descriptor.longtitude << descriptor.longtitudeDirection << "\n";
							cout << "Searching for file " << descriptor.unzippedFile() << " in archive" << "\n";

							SRTMZipDecompressor decompressor;
							int err = decompressor.decompress(path, descriptor.unzippedPath(), descriptor.unzippedFile());
							if (err) {
								cout << "Decompressor returned error: " << err;
							}
							else {
								cout << "Unzipped into " << descriptor.unzippedPath() << "\n";
							}
						}
					} else {
						boost::match_results<std::string::const_iterator> matchingGroups;
						if (boost::regex_match(path, matchingGroups, generalRegex))
						{
							matchingDescriptor = descriptor.fillFromMatchingGroups(matchingGroups);
						}
					}

					if (matchingDescriptor) {
						SRTMHeightFileReader reader;
						short ** heights = reader.readHRTFileIntoBuffer(descriptor.unzippedPath());

						//TODO: Populating real numbers for outliers
						vector<short> original = { 5, 20, 3, 8, 11, 300, 50, 3,12,13,5,8,11,20,-50,30,11,50,48,12,33,6,7,99,33 };
					//	vector<short> original = { 5, 6, 7, 8, 9, 10 };


						SRTMStatisticsMethods statistics;
						vector<short> values = statistics.checkForOutliersUsingIQR(original);

						for (int i = 0; i < values.size(); i++)
						{
							cout << values.at(i) << " " ;
						}
						cout << "\n";

						//TODO: Process heights	

						for (int h = 0; h < SRTM_TILE_HEIGHT; h++) {
							delete[] heights[h];
						}
						delete[] heights;
						
					}


					/*if (!agregatingIntoOneMapFile) {

					}
					else {

					}*/
				}
			} else {
				cout << p << " is not a directory! \n";
				return 1;
			}
		} else {
			cout << p << " does not exist or it is not a folder! \n";
			return 1;
		}

	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		cout << "Got an exception " << ex.what() << '\n';
		return 2;
	}

	return 0;
}