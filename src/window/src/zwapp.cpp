#include<include/window/zwwindow.h>
#include<include/window/zwapp.h>
#include<include/vulkan/zwrender.h>

void ZwApp::excute()
{
    m_pWindow = new ZwWindow();
    m_pWindow->init();

    m_pRender = new ZwRender();
    m_pRender->init(m_pWindow->getGlfwWindow());

    registerFrameBufferCallback();

    mainLoop();
    cleanUp();
}

void ZwApp::mainLoop()
{
    if (!m_pWindow || !m_pRender)
        return;
    GLFWwindow* pWindow = m_pWindow->getGlfwWindow();
    if (!m_pWindow)
        return;
    while (!glfwWindowShouldClose(pWindow))
    {
        glfwPollEvents();
        m_pRender->drawFrame();
    }
    m_pRender->waitIdle();
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

void ZwApp::framebufferResizeCallback(GLFWwindow* pWindow, int width, int height)
{
    auto pRender = reinterpret_cast<ZwRender*>(glfwGetWindowUserPointer(pWindow));
    if (!pRender)
        return;
    pRender->setIsFramebufferResized(true);
}

void ZwApp::registerFrameBufferCallback()
{
    if (!m_pRender || !m_pWindow)
        return;
    glfwSetWindowUserPointer(m_pWindow->getGlfwWindow(), m_pRender);
    glfwSetFramebufferSizeCallback(m_pWindow->getGlfwWindow(), framebufferResizeCallback);
}