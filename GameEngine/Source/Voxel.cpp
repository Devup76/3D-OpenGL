#include "Voxel.h"

Voxel::Voxel() : position(0.0f), color(1.0f), exists(true) {}

Voxel::Voxel(const glm::vec3& pos, const glm::vec3& col, bool exist)
	: position(pos), color(col), exists(exist) {}
