#pragma once
#include "Glad/glad.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>

struct Voxel {

	glm::vec3 position;
	glm::vec3 color;
	bool exists;

	enum VoxelType
	{
		AIR,
		GRASS,
		DIRT,
		STONE
	};

	Voxel();
	Voxel(const glm::vec3& pos, const glm::vec3& col, bool exists);

};

