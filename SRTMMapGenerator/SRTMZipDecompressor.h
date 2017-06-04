#pragma once

#include "stdafx.h"
#include <string>
#include <zip.h>

using namespace std;

class SRTMZipDecompressor
{
public:
	SRTMZipDecompressor();
	~SRTMZipDecompressor();

	int decompress(string source, string destination, string searchingForFile);
};

