#include <include/window/zwwindow.h>
#include <include/window/windowconst.h>

void ZwWindow::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_pWindow = glfwCreateWindow(ZWWINDOW_WIDTH, ZWWINDOW_HEIGHT, ZWWINDOW_NAME, nullptr, nullptr);
}

void ZwWindow::destroy()
{
    if (!m_pWindow)
        return;
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();

    m_pWindow = nullptr;
}