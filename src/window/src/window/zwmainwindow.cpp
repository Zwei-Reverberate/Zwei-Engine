#include <include/window/zwmainwindow.h>
#include <include/const/windowconst.h>
#include <include/window/glfwcallback.h>
#include <include/ui/propertydockwidget.h>
#include <include/ui/resourcebrowserdockwidget.h>
#include <include/ui/scenetreedockwidget.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <QVBoxLayout>
#include <QPushButton>
#include <qtoolbar.h>
#include <qdockwidget.h>
#include <qstatusbar.h>

void ZwMainWindow::init()
{
    initGlfw();
    initToolBar();
    initDockWidget();
    initConverWindow();

    this->setWindowTitle(ZWWINDOW_NAME);
    this->showMaximized();
    glfwShowWindow(m_pGlfwWindow);
}

void ZwMainWindow::initGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // 创建时先隐藏
    m_pGlfwWindow = glfwCreateWindow(ZWWINDOW_WIDTH, ZWWINDOW_HEIGHT, ZWWINDOW_NAME, nullptr, nullptr);

    void* pNativeWindow = glfwGetWin32Window(m_pGlfwWindow);
    if (!pNativeWindow)
        return;
    m_pConvertWindow = QWindow::fromWinId((WId)pNativeWindow);
    if (!m_pConvertWindow)
        return;
    registerGlfwCallBacks();
}

void ZwMainWindow::initToolBar()
{
    m_pToolBar = new ZwToolBar(this); 
    this->addToolBar(Qt::TopToolBarArea, m_pToolBar);
}

void ZwMainWindow::initDockWidget()
{
    // 添加左侧场景树
    SceneTreeDockWidget* sceneTreeDock = new SceneTreeDockWidget("Scene Tree", this);
    addDockWidget(Qt::LeftDockWidgetArea, sceneTreeDock);

    // 添加右侧属性框
    PropertyDockWidget* propertyDock = new PropertyDockWidget("Properties", this);
    addDockWidget(Qt::RightDockWidgetArea, propertyDock);

    // 添加底部资源浏览器
    ResourceBrowserDockWidget* resourceBrowserDock = new ResourceBrowserDockWidget("Resource Browser", this);
    addDockWidget(Qt::BottomDockWidgetArea, resourceBrowserDock);
}

void ZwMainWindow::initConverWindow()
{

    QWidget* pCentralWidget = new QWidget(this);
    pCentralWidget->setFixedSize(QSize(ZWWINDOW_WIDTH, ZWWINDOW_HEIGHT));
    this->setCentralWidget(pCentralWidget);

    QVBoxLayout* pLayout = new QVBoxLayout(pCentralWidget);

    QWidget* pWindowContainer = QWidget::createWindowContainer(getQWindow(), this);
    pLayout->addWidget(pWindowContainer);
}

void ZwMainWindow::destroy()
{
    if (!m_pGlfwWindow || !m_pConvertWindow)
        return;
    glfwDestroyWindow(m_pGlfwWindow);
    glfwTerminate();
    m_pConvertWindow->deleteLater();
}

bool ZwMainWindow::isZwWindowClosed() const
{
    return m_isWindowClosed;
}

void  ZwMainWindow::closeEvent(QCloseEvent* event)
{
    m_isWindowClosed = true;
}


void ZwMainWindow::registerGlfwCallBacks()
{
    if (!m_pGlfwWindow)
        return;
    glfwSetMouseButtonCallback(m_pGlfwWindow, GlfwCallback::mouseButtonCallback);
    glfwSetCursorPosCallback(m_pGlfwWindow, GlfwCallback::cursorPositionCallback);
    glfwSetScrollCallback(m_pGlfwWindow, GlfwCallback::mouseScrollCallback);
}