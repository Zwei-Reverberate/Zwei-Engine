#ifndef GLFWCALLBACK_H
#define GLFWCALLBACK_H
#include <GLFW/glfw3.h>

namespace GlfwCallback
{
	void mouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods);

	void cursorPositionCallback(GLFWwindow* pWindow, double xpos, double ypos);

	void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
}

#endif // !GLFWCALLBACK_H
