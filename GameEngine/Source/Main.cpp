#include <iostream>
#include <string>
#include "Glad/glad.h"
#include "guiManager.h"
#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shaders/Include/Shader.h"
#include "Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
void wireframeModeToggle();
void updateFPS(GLFWwindow* window);

// Screen Settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;
std::string fpsString;

// Grid settings
const int GRID_SIZE = 4;
glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f);

// Chunk settings
int chunkWidth = 3;
int chunkHeight = 1;
int chunkDepth = 1;
int chunkSpacing = GRID_SIZE;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 105.0f;

// Timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main() {

	// Init GLFW and configure the version/window settings
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3D Program", NULL, NULL);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	guiManager gm(window);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Load all OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader("GameEngine/Include/Shaders/Source/vertexShader.glsl", "GameEngine/Include/Shaders/Source/fragmentShader.glsl");
	Renderer renderer;

	VoxelGrid voxelGrid(GRID_SIZE);
	renderer.initializeVoxelGrid(voxelGrid);

	// Render Loop
	while (!glfwWindowShouldClose(window)) {
		updateFPS(window);

		// per-frame time logic
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Input
		processInput(window);
		
		// Render
		glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set up transformations
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 1000.0f);
		GLuint projectionLoc = glGetUniformLocation(shader.use(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		GLuint viewLoc = glGetUniformLocation(shader.use(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 viewProjection = projection * view;

		gm.create();

		//renderer.renderGrid(shader.use(), voxelGrid, offset);
		renderer.renderChunks(shader.use(), voxelGrid, offset, chunkWidth, chunkHeight, chunkDepth, chunkSpacing);
		renderer.printNumRenderedVoxels(); // Debug

		ImGui::Begin("Debug Window");
		ImGui::Text("Hello, there adventurer!");
		ImGui::Spacing();
		ImGui::Text(fpsString.c_str());
		ImGui::Spacing();
		ImGui::Text("Entire Grid x, y, z Coords:");
		ImGui::SliderFloat("x", &offset.x, -100.0f, 100.0f);
		ImGui::SliderFloat("y", &offset.y, -100.0f, 100.0f);
		ImGui::SliderFloat("z", &offset.z, -100.0f, 100.0f);
		ImGui::Spacing();
		ImGui::SliderInt("Chunk Width", &chunkWidth, 1, 25);
		ImGui::SliderInt("Chunk Height", &chunkHeight, 1, 25);
		ImGui::SliderInt("Chunk Depth", &chunkDepth, 1, 25);
		ImGui::SliderInt("Chunk Spacing", &chunkSpacing, 0, 100);
		ImGui::Spacing();
		if (ImGui::Button("Toggle Wireframe")) {
			wireframeModeToggle();
		}

		ImGui::End();

		gm.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up and exit
	renderer.cleanup();

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = static_cast<float>(10.0f * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	// Reset xyz
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		offset = glm::vec3(0.f, 0.0f, 0.0f);

	// Render in wireframe mode
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
		static bool wireframeMode = false;

		if (wireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		wireframeMode = !wireframeMode;
	}
		
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureMouse) {

		return;
	}

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.5f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void wireframeModeToggle() {
	static bool wireframeMode = false;
	
	if (wireframeMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	wireframeMode = !wireframeMode;
}

void updateFPS(GLFWwindow* window)
{
	static double lastTime = glfwGetTime();
	static int frameCount = 0;

	double currentTime = glfwGetTime();
	frameCount++;

	if (currentTime - lastTime >= 1.0) {
		double fps = static_cast<double>(frameCount) / (currentTime - lastTime);
		fpsString = "FPS: " + std::to_string(fps);

		frameCount = 0;
		lastTime += 1.0;
	}
}
