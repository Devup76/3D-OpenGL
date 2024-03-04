#pragma once
#include "Glad/glad.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>
#include <vector>

class RenderPipeline
{
public:

	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
	};

	RenderPipeline();
	~RenderPipeline();

	glm::vec3 calculateOffsetBasedOnNoise(int x, int y, int z);
	void drawChunk(unsigned int shaderProgram, int gridWidth, int gridHeight, glm::vec3 chunkOffset, float planeSpacing);

	void cleanUp();
	void ec();

private:

	GLuint _VAO, _VBO, _EBO;

	static const float planeVertices[];
	static const unsigned int planeIndices[];

};

