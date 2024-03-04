#pragma once
#include "Voxel.h"
#include <vector>

class VoxelGrid
{
private:

	static const std::vector<glm::mat4> matrices;

public:

	const int GRID_SIZE;
	std::vector<std::vector<std::vector<Voxel>>> grid;

	VoxelGrid(int size);
	bool isExposedFace(int x, int y, int z) const;
	
	Voxel& getVoxel(int x, int y, int z);

	void ec();
	bool isValidIndex(int x, int y, int z, const int gridSize) const;

};

