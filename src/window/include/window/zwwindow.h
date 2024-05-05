#ifndef ZWWINDOW_H
#define ZWWINDOW_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class ZwWindow
{
public:
    void init();
    void destroy();
    GLFWwindow* getGlfwWindow() const { return m_pWindow; };
private:
    GLFWwindow* m_pWindow = nullptr;
};

#endif