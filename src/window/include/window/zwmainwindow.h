#ifndef ZWMAINWINDOW_H
#define ZWWINDOWCONTAINER_H
#include <GLFW/glfw3.h>
#include <qwindow.h>
#include <qmainwindow.h>
#include <include/ui/zwtoolbar.h>

class ZwMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void init();
    void destroy();
    bool isZwWindowClosed() const;
    GLFWwindow* getGlfwWindow() const { return m_pGlfwWindow; };
    QWindow* getQWindow() const { return m_pConvertWindow; }

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void registerGlfwCallBacks();
    void initGlfw();
    void initToolBar();
    void initDockWidget();
    void initConverWindow();

private:
    GLFWwindow* m_pGlfwWindow = nullptr;
    QWindow* m_pConvertWindow = nullptr;

    ZwToolBar* m_pToolBar = nullptr;

    bool m_isWindowClosed = false;
};

#endif