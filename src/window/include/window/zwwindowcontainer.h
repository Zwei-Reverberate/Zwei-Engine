#ifndef ZWWINDOWCONTAINER_H
#define ZWWINDOWCONTAINER_H
#include <GLFW/glfw3.h>
#include <qwindow.h>

class ZwWindow;
class ZwWindowContainer : public QObject
{
    Q_OBJECT

public:
    void init();
    void destroy();
    bool isZwWindowClosed() const;
    GLFWwindow* getGlfwWindow() const { return m_pGlfwWindow; };
    ZwWindow* getQWindow() const { return m_pZwWindow; }

private:
    void registerGlfwCallBacks();

private:
    GLFWwindow* m_pGlfwWindow = nullptr;
    ZwWindow* m_pZwWindow = nullptr;
};

#endif