#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

const float Renderer::cubeVertices[]{
    // Front face
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  // Front Bottom Left
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  // Front Bottom Right
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  // Front Top Right
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  // Front Top Right
    -0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  // Front Top Left
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  // Front Bottom Left

    // Back face
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Back Bottom Left
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Back Bottom Right
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Back Top Right
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Back Top Right
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Back Top Left
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  // Back Bottom Left

    // Left face
    -0.5f, -0.5f,  0.5f, 1.0f,  1.0f,  1.0f,  // Left Bottom Front
    -0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  1.0f,  // Left Bottom Back
    -0.5f,  0.5f, -0.5f, 1.0f,  1.0f,  1.0f,  // Left Top Back
    -0.5f,  0.5f, -0.5f, 1.0f,  1.0f,  1.0f,  // Left Top Back
    -0.5f,  0.5f,  0.5f, 1.0f,  1.0f,  1.0f,  // Left Top Front
    -0.5f, -0.5f,  0.5f, 1.0f,  1.0f,  1.0f,  // Left Bottom Front

    // Right face
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // Right Bottom Front
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // Right Bottom Back
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // Right Top Back
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  // Right Top Back
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // Right Top Front
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  // Right Bottom Front

    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  // Top Left Front
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  // Top Right Front
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // Top Right Back
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // Top Right Back
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  // Top Left Back
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  // Top Left Front

    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  // Bottom Left Front
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  // Bottom Right Front
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  // Bottom Right Back
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  // Bottom Right Back
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  // Bottom Left Back
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  // Bottom Left Front

};

const GLuint Renderer::cubeIndices[]{
    // Front face
    0, 1, 2, 3, 4, 5,

    // Back face
    11, 10, 9, 8, 7, 6,

    // Left face
    12, 13, 14, 15, 16, 17,

    // Right face
    18, 19, 20, 21, 22, 23,

    // Top face
    24, 25, 26, 27, 28, 29,

    // Bottom face
    35, 34, 33, 32, 31, 30
};

Renderer::Renderer() {
	init();
}

void Renderer::init()
{
    // Set up vertex array object (VAO), and vertex buffer object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO and copy vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Bind IBO and copy index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);


    // Set vertex position pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set color coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set offset attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // Unbind VAO, and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable multisampling
    glEnable(GL_MULTISAMPLE);

    // Enable Front-Face Culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
}

void Renderer::renderVoxel(unsigned int shaderProgram, const glm::mat4 transformationMatrix, bool renderFront, bool renderBack, bool renderLeft, bool renderRight, bool renderTop, bool renderBottom)
{
    glUseProgram(shaderProgram);  // Bind the shader program before setting uniforms

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(transformationMatrix));
    // Color (or texture) uniform
    // need to figure out
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Render only faces that should be neighbors
    GLuint numberOfVerticesPerFace = 6;
    if (renderFront) {
        GLuint startVertexIndexForFrontFace = 0;

        //glDrawArrays(GL_TRIANGLES, startVertexIndexForFrontFace, numberOfVerticesPerFace);
        glDrawElements(GL_TRIANGLES, numberOfVerticesPerFace, GL_UNSIGNED_INT, (void*)(startVertexIndexForFrontFace * sizeof(GLuint)));
    }
    if (renderBack) {
        GLuint startVertexIndexForBackFace = 6;

        //glDrawArrays(GL_TRIANGLES, startVertexIndexForBackFace, numberOfVerticesPerFace);
        glDrawElements(GL_TRIANGLES, numberOfVerticesPerFace, GL_UNSIGNED_INT, (void*)(startVertexIndexForBackFace * sizeof(GLuint)));
    }
    if (renderLeft) {
        GLuint startVertexIndexForLeftFace = 12;

        //glDrawArrays(GL_TRIANGLES, startVertexIndexForLeftFace, numberOfVerticesPerFace);
        glDrawElements(GL_TRIANGLES, numberOfVerticesPerFace, GL_UNSIGNED_INT, (void*)(startVertexIndexForLeftFace * sizeof(GLuint)));
    }
    if (renderRight) {
        GLuint startVertexIndexForRightFace = 18;

        //glDrawArrays(GL_TRIANGLES, startVertexIndexForRightFace, numberOfVerticesPerFace);
        glDrawElements(GL_TRIANGLES, numberOfVerticesPerFace, GL_UNSIGNED_INT, (void*)(startVertexIndexForRightFace * sizeof(GLuint)));
    }
    if (renderTop) {
        GLuint startVertexIndexForTopFace = 24;

        //glDrawArrays(GL_TRIANGLES, startVertexIndexForTopFace, numberOfVerticesPerFace);
        glDrawElements(GL_TRIANGLES, numberOfVerticesPerFace, GL_UNSIGNED_INT, (void*)(startVertexIndexForTopFace * sizeof(GLuint)));
    }
    if (renderBottom) {
        GLuint startVertexIndexForBottomFace = 30;

        //glDrawArrays(GL_TRIANGLES, startVertexIndexForBottomFace, numberOfVerticesPerFace);
        glDrawElements(GL_TRIANGLES, numberOfVerticesPerFace, GL_UNSIGNED_INT, (void*)(startVertexIndexForBottomFace * sizeof(GLuint)));
    }

    // Render all of the indices in the VBO *Chuckles* "I'm in danger"
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::initializeVoxelGrid(VoxelGrid& voxelGrid) 
{

    for (int x = 0; x < voxelGrid.GRID_SIZE; x++) {
        for (int y = 0; y < voxelGrid.GRID_SIZE; y++) {
            for (int z = 0; z < voxelGrid.GRID_SIZE; z++) {
                voxelGrid.grid[x][y][z].position = glm::vec3(x, y, z);
                //std::cout << "INITIALIZE_VOXEL_GRID_POSITION::VOXEL::" << "(" << x << ", " << y << ", " << z << ")" << " " << "EXISTS::" << voxelGrid.grid[x][y][z].exists << std::endl;
            }
        }
    }
}

void Renderer::renderGrid(unsigned int shaderProgram, VoxelGrid& voxelGrid, glm::vec3 offset)
{

    for (int x = 0; x < voxelGrid.GRID_SIZE; x++) {
        for (int y = 0; y < voxelGrid.GRID_SIZE; y++) {
            for (int z = 0; z < voxelGrid.GRID_SIZE; z++) {

                Voxel& currentVoxel = voxelGrid.getVoxel(x, y, z);

                if (renderedVoxelsCount == voxelGrid.GRID_SIZE + 2) {
                    isGridInitialized = true;
                    std::cout << "isGridInitialized true" << std::endl;
                }
                else {
                    renderFront = voxelGrid.isExposedFace(x, y, z - 1);
                    renderBack = voxelGrid.isExposedFace(x, y, z + 1);
                    renderLeft = voxelGrid.isExposedFace(x - 1, y, z);
                    renderRight = voxelGrid.isExposedFace(x + 1, y, z);
                    renderTop = voxelGrid.isExposedFace(x, y + 1, z);
                    renderBottom = voxelGrid.isExposedFace(x, y - 1, z);
                    //std::cout << "isExposedFace Ran" << std::endl;
                }

                //std::cout << "Voxel Exists: " << currentVoxel.exists << std::endl;

                if (currentVoxel.exists) {
                    renderedVoxelsCount++;
                    glm::vec3 spacingOffset = glm::vec3(voxelGrid.grid[x][y][z].position.x * (voxelGrid.GRID_SIZE - offset.x), voxelGrid.grid[x][y][z].position.y * (voxelGrid.GRID_SIZE - offset.y), voxelGrid.grid[x][y][z].position.z * (voxelGrid.GRID_SIZE - offset.z));
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), voxelGrid.grid[x][y][z].position + offset);
                    renderVoxel(shaderProgram, transform, renderFront, renderBack, renderLeft, renderRight, renderTop, renderBottom);
                }
            }
        }
    }
}

void Renderer::renderChunks(unsigned int shaderProgam, VoxelGrid& voxelGrid, glm::vec3 offset, int chunkWidth, int chunkHeight, int chunkDepth, int chunkSpacing)
{
    for (int x = 0; x < chunkWidth; x++) {
        for (int y = 0; y < chunkHeight; y++) {
            for (int z = 0; z < chunkDepth; z++) {
                glm::vec3 translation = offset + glm::vec3(x * chunkSpacing, y * chunkSpacing, z * chunkSpacing);

                glm::mat4 transformationMatrix = glm::translate(glm::mat4(1.0f), translation);

                renderGrid(shaderProgam, voxelGrid, translation);
            }
        }
    }
}

void Renderer::cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::printNumRenderedVoxels()
{
    
    if (this->hasPrinted == false) {
        std::cout << "Number of voxels: " << renderedVoxelsCount << std::endl;
        hasPrinted = true;
    }
}