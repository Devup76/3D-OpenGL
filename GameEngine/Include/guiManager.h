#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "Shaders/Include/Shader.h"

class guiManager
{
public:
	guiManager(GLFWwindow* window);
	~guiManager();

	void init(GLFWwindow* window);
	void create();
	void render();
	void destroy();

	bool WantCaptureMouse();
	bool WantCaptureKeyboard();

private:
};

