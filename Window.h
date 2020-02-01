#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
class Window
{
public:
	Window() {}
	/*Properties*/
	GLFWwindow* glfwWindow;
	int width = 1920;
	int height = 1080;
};

