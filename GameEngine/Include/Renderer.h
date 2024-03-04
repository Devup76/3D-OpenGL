#pragma once
#include "VoxelGrid.h"
class Renderer
{
private:
	GLuint VAO, VBO, IBO, matrixBuffer;
	static const float cubeVertices[];
	static const GLuint cubeIndices[];

	int renderedVoxelsCount = 0;
	bool hasPrinted = false;
	bool isGridInitialized = false;

	bool renderFront;
	bool renderBack;
	bool renderLeft;
	bool renderRight;
	bool renderTop;
	bool renderBottom;

public:
	Renderer();
	void init();
	// Advanced renderVoxel
	void renderVoxel(unsigned int shaderProgram, const glm::mat4 transformationMatrix, bool renderFront, bool renderBack, bool renderLeft, bool renderRight, bool renderTop, bool renderBottom);
	void initializeVoxelGrid(VoxelGrid& voxelGrid);
	void renderGrid(unsigned int shaderProgram, VoxelGrid& voxelGrid, glm::vec3 offset);
	void renderChunks(unsigned int shaderProgam, VoxelGrid& voxelGrid, glm::vec3 offset, int chunkwidth, int chunkHeight, int chunkDepth, int chunkSpacing);
	void cleanup();

	// Utility
	void printNumRenderedVoxels();
};

