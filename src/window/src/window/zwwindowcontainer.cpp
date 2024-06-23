#include <include/window/zwwindowcontainer.h>
#include <include/const/windowconst.h>
#include <include/window/zwwindow.h>
#include <include/window/glfwcallback.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

void ZwWindowContainer::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // 创建时先隐藏
    m_pGlfwWindow = glfwCreateWindow(ZWWINDOW_WIDTH, ZWWINDOW_HEIGHT, ZWWINDOW_NAME, nullptr, nullptr);

    m_pZwWindow = new ZwWindow();
    m_pZwWindow->setTitle(QString(ZWWINDOW_NAME));
    void* pNativeWindow = glfwGetWin32Window(m_pGlfwWindow);
    if (!pNativeWindow)
        return;
    QWindow* pConvertWindow = QWindow::fromWinId((WId)pNativeWindow);
    if (!pConvertWindow)
        return;

    pConvertWindow->setParent(m_pZwWindow);
    pConvertWindow->setPosition(QPoint(0, 0));
    glfwShowWindow(m_pGlfwWindow); // 嵌入 QWindow 后显示

    registerGlfwCallBacks();

    m_pZwWindow->showMaximized();
}

void ZwWindowContainer::destroy()
{
    if (!m_pGlfwWindow || !m_pZwWindow)
        return;
    glfwDestroyWindow(m_pGlfwWindow);
    glfwTerminate();
    m_pZwWindow->deleteLater();
    // m_pQWindow = nullptr;
    // m_pGlfwWindow = nullptr;
}

bool ZwWindowContainer::isZwWindowClosed() const
{
    if (!m_pZwWindow)
        return false;
    return m_pZwWindow->getIsClosed();
}


void ZwWindowContainer::registerGlfwCallBacks()
{
    if (!m_pGlfwWindow)
        return;
    glfwSetMouseButtonCallback(m_pGlfwWindow, GlfwCallback::mouseButtonCallback);
    glfwSetCursorPosCallback(m_pGlfwWindow, GlfwCallback::cursorPositionCallback);
    glfwSetScrollCallback(m_pGlfwWindow, GlfwCallback::mouseScrollCallback);
}