#include "RenderPipeline.h"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_access.hpp"

#include "Shaders/Include/Shader.h"
#include <glm/gtc/type_ptr.hpp>

// Vertices for a single plane (two triangles)
const float RenderPipeline::planeVertices[] = {
    // First triangle
    0.0f, 0.0f, 0.0f,  // Vertex 1: (x, y, z) = (0, 0, 0)
    1.0f, 0.0f, 0.0f,  // Vertex 2: (x, y, z) = (1, 0, 0)
    1.0f, 0.0f, 1.0f,  // Vertex 3: (x, y, z) = (1, 0, 1)

    // Second triangle
    1.0f, 0.0f, 1.0f,  // Vertex 3: (x, y, z) = (1, 0, 1)
    0.0f, 0.0f, 1.0f,  // Vertex 4: (x, y, z) = (0, 0, 1)
    0.0f, 0.0f, 0.0f   // Vertex 1: (x, y, z) = (0, 0, 0) (Repeated for the second triangle)
};

const unsigned int RenderPipeline::planeIndices[] = {
    0, 1, 2,  // Front face
    3, 4, 5,  // Front face
};

/*

RenderPipeline::RenderPipeline()
{

    // Set up vertex array object (VAO), vertex buffer object (VBO), and element buffer object (EBO)
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

    // Bind VAO
    glBindVertexArray(_VAO);

    // Bind VBO and copy vertex data
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Bind EBO and copy index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Set vertex position pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Set color coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set offset attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // Unbind VAO, VBO, and EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

}

RenderPipeline::~RenderPipeline()
{
    cleanUp();
}

glm::vec3 RenderPipeline::calculateOffsetBasedOnNoise(int x, int y, int z)
{
    float frequency = 0.5f;
    float amplitude = 0.5f;

    // Use sin wave noise to generate offsets for x, y, and z
    float offsetX = amplitude * sin(frequency * x);
    float offsetY = amplitude * sin(frequency * x) * sin(frequency * z);
    float offsetZ = amplitude * sin(frequency * z);

    // Scale the offsets to your desired range
    float scale = 5.0f; // Adjust as needed
    glm::vec3 offset(offsetX * scale, offsetY * scale, offsetZ * scale);

    return offset;
}


void RenderPipeline::drawChunk(unsigned int shaderProgram, int gridWidth, int gridHeight, glm::vec3 chunkOffset, float planeSpacing) 
{

    // Retrieve uniform locations for transform and color
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");

    // Set up and use shader program
    glUseProgram(shaderProgram);

    glBindVertexArray(_VAO);

    for (int z = 0; z < gridHeight; ++z)
    {
        for (int x = 0; x < gridWidth; ++x)
        {
            glm::mat4 model = glm::mat4(1.0f);

            // Calculate the offset for the current plane based on its size and spacing
            glm::vec3 planeOffset = glm::vec3(x * (planeWidth + planeSpacing), 0.0f, z * (planeHeight + planeSpacing));

            model = glm::translate(model, planeOffset);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // Draw the plane using indices
        }
    }

    glBindVertexArray(0);
}
*/

void RenderPipeline::cleanUp()
{
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
}

void RenderPipeline::ec() {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}
