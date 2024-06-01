#include <include/window/zwwindowcontainer.h>
#include <include/window/zwapp.h>
#include <include/vulkan/zwrender.h>
#include <qwidget.h>
#include <GLFW/glfw3.h>


ZwApp::ZwApp(int& argc, char** argv):QApplication(argc, argv)
{
}

void ZwApp::excute()
{
    m_pWindowContainer = new ZwWindowContainer();
    m_pWindowContainer->init();

    m_pRender = new ZwRender();
    m_pRender->init(m_pWindowContainer->getGlfwWindow());

    registerFrameBufferCallback();

    mainLoop();
    cleanUp();
}

void ZwApp::mainLoop()
{
    if (!m_pWindowContainer || !m_pRender)
        return;
    GLFWwindow* pWindow = m_pWindowContainer->getGlfwWindow();
    if (!m_pWindowContainer)
        return;
    while (!glfwWindowShouldClose(pWindow))
    {
        glfwPollEvents();

        if (m_pWindowContainer->isZwWindowClosed())
            break;

        m_pRender->drawFrame();
    }
    m_pRender->waitIdle();
}

void ZwApp::cleanUp()
{
    if (!m_pWindowContainer || !m_pRender)
        return;
    m_pWindowContainer->destroy();
    m_pRender->destroy();
    m_pWindowContainer->deleteLater();
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
    if (!m_pRender || !m_pWindowContainer)
        return;
    glfwSetWindowUserPointer(m_pWindowContainer->getGlfwWindow(), m_pRender);
    glfwSetFramebufferSizeCallback(m_pWindowContainer->getGlfwWindow(), framebufferResizeCallback);
}