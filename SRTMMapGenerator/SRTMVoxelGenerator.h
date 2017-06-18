#pragma once

#include "stdafx.h"
#include <iterator>
#include <algorithm>
#include <vector>

#include "SRTMConstants.h"

using namespace std;

struct SRTMPartialVoxel {
	short x;
	short y;
	short z;
};

struct SRTMVoxelBlock {
	short numberOfVoxels;
	vector<SRTMPartialVoxel> voxels;
};

struct SRTMVoxelGeneratorDescriptor
{
	short currentHeight;
	short currentWidth;
	short lowestPoint;
};

class SRTMVoxelGenerator
{
public:
	SRTMVoxelGenerator();
	~SRTMVoxelGenerator();

	SRTMVoxelBlock generateVoxelBlock(
		short ** heightsBuffer,
		SRTMVoxelGeneratorDescriptor descriptor
	);

	bool writeBlockDirectyIntoStream(ostream& out,
		short ** heightsBuffer,
		SRTMVoxelGeneratorDescriptor descriptor
	);
};

