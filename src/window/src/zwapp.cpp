#include<include/window/zwwindow.h>
#include<include/window/zwapp.h>
#include<include/vulkan/zwrender.h>

void ZwApp::excute()
{
    m_pWindow = new ZwWindow();
    m_pWindow->init();

    m_pRender = new ZwRender();
    m_pRender->init(m_pWindow->getGlfwWindow());

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
    if (!m_pWindow || !m_pRender)
        return;
    m_pWindow->destroy();
    m_pRender->destroy();
    m_pWindow = nullptr;
    m_pRender = nullptr;
}
