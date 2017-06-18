#include "stdafx.h"
#include "SRTMVoxelGenerator.h"


SRTMVoxelGenerator::SRTMVoxelGenerator()
{
}


SRTMVoxelGenerator::~SRTMVoxelGenerator()
{
}

SRTMVoxelBlock SRTMVoxelGenerator::generateVoxelBlock(
	short ** heightsBuffer,
	SRTMVoxelGeneratorDescriptor descriptor
) {



	if (!descriptor.currentHeight || 
		!descriptor.currentWidth ||
		descriptor.currentHeight == SRTM_TILE_HEIGHT - 1 || 
		descriptor.currentWidth == SRTM_TILE_WIDTH - 1) {

		short numberOfResultVoxels = heightsBuffer[descriptor.currentHeight][descriptor.currentWidth];

		SRTMPartialVoxel *voxels = new SRTMPartialVoxel[numberOfResultVoxels];
		for (int v = 0; v < numberOfResultVoxels; v++) {
			SRTMPartialVoxel voxel;
			voxel.x = descriptor.currentWidth;
			voxel.y = descriptor.currentHeight;
			voxel.z = v;

			voxels[v] = voxel;
		}

		SRTMVoxelBlock block;
		block.numberOfVoxels = numberOfResultVoxels;
		block.voxels.insert(block.voxels.begin(), voxels, voxels + numberOfResultVoxels);

		delete[] voxels;

		return block;
	}

	short m[4] = {
		heightsBuffer[descriptor.currentHeight - 1][descriptor.currentWidth],
		heightsBuffer[descriptor.currentHeight + 1][descriptor.currentWidth],
		heightsBuffer[descriptor.currentHeight][descriptor.currentWidth - 1],
		heightsBuffer[descriptor.currentHeight][descriptor.currentWidth + 1]
	};

	short min = *min_element(m, m + 4);
	short currentHeight = heightsBuffer[descriptor.currentHeight][descriptor.currentWidth];

	if (currentHeight > min) {
		short numberOfVoxels = currentHeight - min + 1;
		SRTMPartialVoxel *voxels = new SRTMPartialVoxel[numberOfVoxels];
		for (int v = 0; v < numberOfVoxels; v++) {
			SRTMPartialVoxel voxel;
			voxel.x = descriptor.currentWidth;
			voxel.y = descriptor.currentHeight;
			voxel.z = min + v;

			voxels[v] = voxel;
		}

		SRTMVoxelBlock block;
		block.numberOfVoxels = numberOfVoxels;
		block.voxels.insert(block.voxels.begin(), voxels, voxels + numberOfVoxels);

		delete[] voxels;

		return block;
	}
	else {
		SRTMPartialVoxel voxel;
		voxel.x = descriptor.currentWidth;
		voxel.y = descriptor.currentHeight;
		voxel.z = currentHeight;

		SRTMVoxelBlock block;
		block.numberOfVoxels = 1;
		block.voxels.push_back(voxel);
	}
}

bool SRTMVoxelGenerator::writeBlockDirectyIntoStream(ostream& out,
	short ** heightsBuffer,
	SRTMVoxelGeneratorDescriptor descriptor
) {

	short height = heightsBuffer[descriptor.currentHeight][descriptor.currentWidth];
	short corrigatedHeight = height - descriptor.lowestPoint;

	if (!descriptor.currentHeight ||
		!descriptor.currentWidth ||
		descriptor.currentHeight == SRTM_TILE_HEIGHT - 1 ||
		descriptor.currentWidth == SRTM_TILE_WIDTH - 1) {

		short numberOfResultVoxels = corrigatedHeight;

		out.write((char*)&numberOfResultVoxels, sizeof(short));

		for (int v = 0; v < numberOfResultVoxels; v++) {
			out.write((char*)&descriptor.currentWidth, sizeof(short));
			out.write((char*)&descriptor.currentHeight, sizeof(short));
			out.write((char*)&v, sizeof(short));
		}
		return true;
	}

	short m[4] = {
		heightsBuffer[descriptor.currentHeight - 1][descriptor.currentWidth] - descriptor.lowestPoint,
		heightsBuffer[descriptor.currentHeight + 1][descriptor.currentWidth] - descriptor.lowestPoint,
		heightsBuffer[descriptor.currentHeight][descriptor.currentWidth - 1] - descriptor.lowestPoint,
		heightsBuffer[descriptor.currentHeight][descriptor.currentWidth + 1] - descriptor.lowestPoint
	};

	short min = *min_element(m, m + 4);
	short currentHeight = corrigatedHeight;

	if (currentHeight > min) {
		short numberOfVoxels = currentHeight - min + 1;
		out.write((char*)&numberOfVoxels, sizeof(short));

		for (int v = 0; v < numberOfVoxels; v++) {
			out.write((char*)&descriptor.currentWidth, sizeof(short));
			out.write((char*)&descriptor.currentHeight, sizeof(short));
			out.write((char*)&v, sizeof(short));
		}
		return true;
	}
	else {
		short numberOfVoxels = 1;
		out.write((char*)&numberOfVoxels, sizeof(short));
		out.write((char*)&descriptor.currentWidth, sizeof(short));
		out.write((char*)&descriptor.currentHeight, sizeof(short));
		out.write((char*)&currentHeight, sizeof(short));
		return true;
	}
}