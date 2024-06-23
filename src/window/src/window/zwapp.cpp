#include <include/windowevent/camerarotateevent.h>
#include <include/windowevent/camerazoomevent.h>
#include <include/windowevent/cameramoveevent.h>
#include <include/window/zwwindowcontainer.h>
#include <include/window/zwapp.h>
#include <include/vulkan/zwrender.h>
#include <include/time/timer.h>
#include <qwidget.h>
#include <GLFW/glfw3.h>
#include <iostream>

ZwApp::ZwApp(int& argc, char** argv):QApplication(argc, argv)
{
    addListener();
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

    Timer appTimer{};
    while (!glfwWindowShouldClose(pWindow))
    {
        glfwPollEvents();

        if (m_pWindowContainer->isZwWindowClosed())
            break;

        appTimer.startFrame();
        m_pRender->drawFrame();

      // double fps = appTimer.getFps();
      // std::cout << "FPS: " << fps << std::endl;
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


void ZwApp::addListener()
{
    EventManager* pEventManager = EventManager::getEventManager();
    if (!pEventManager)
        return;

    std::shared_ptr<CameraRotateListener> cameraRotateListener = std::make_shared<CameraRotateListener>();
    auto cameraRotateCallback = std::make_shared<EventManager::EventCallback>
    (
            [cameraRotateListener](const Event& event) { cameraRotateListener->onEvent(event); }
    );
    pEventManager->addListener(CAMERA_ROTATE_EVENT_NAME, cameraRotateCallback );


    std::shared_ptr<CameraZoomListener> cameraZoomListener = std::make_shared<CameraZoomListener>();
    auto cameraZoomCallback = std::make_shared<EventManager::EventCallback>
    (
            [cameraZoomListener](const Event& event) { cameraZoomListener->onEvent(event); }
    );
    pEventManager->addListener(CAMERA_ZOOM_EVENT_NAME, cameraZoomCallback);


    std::shared_ptr<CameraMoveListener> cameraMoveListener = std::make_shared<CameraMoveListener>();
    auto cameraMoveCallback = std::make_shared<EventManager::EventCallback>
    (
            [cameraMoveListener](const Event& event) { cameraMoveListener->onEvent(event); }
    );
    pEventManager->addListener(CAMERA_MOVE_EVENT_NAME, cameraMoveCallback);
}