#include<include/window/zwwindow.h>
#include<include/window/zwapp.h>

void ZwApp::excute()
{
    m_pWindow = new ZwWindow();
    m_pWindow->init();
    mainLoop();
    cleanUp();
}

void ZwApp::mainLoop()
{
    if (!m_pWindow)
        return;
    GLFWwindow* pWindow = m_pWindow->getGlfwWindow();
    if (!m_pWindow)
        return;
    while (!glfwWindowShouldClose(pWindow))
    {
        glfwPollEvents();
    }

}

void ZwApp::cleanUp()
{
    if (!m_pWindow)
        return;
    m_pWindow->destroy();
    m_pWindow = nullptr;
}
