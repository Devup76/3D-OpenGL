#include "guiManager.h"

guiManager::guiManager(GLFWwindow* window)
{
	init(window);
}

guiManager::~guiManager()
{
	destroy();
}

void guiManager::init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void guiManager::create()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void guiManager::render()
{

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void guiManager::destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool guiManager::WantCaptureMouse()
{
	return ImGui::GetIO().WantCaptureMouse;
	
}

bool guiManager::WantCaptureKeyboard()
{
	return ImGui::GetIO().WantCaptureKeyboard;
}
