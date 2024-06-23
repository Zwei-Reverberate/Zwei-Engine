#ifndef ZWAPP_H
#define ZWAPP_H
#include <qapplication.h>

class GLFWwindow;
class ZwWindowContainer;
class ZwRender;
class ZwApp : public QApplication
{
    Q_OBJECT
public:
    ZwApp(int& argc, char** argv);
    void excute();

private:
    void mainLoop();
    void cleanUp();
    void registerFrameBufferCallback();
    void addListener();
    static void framebufferResizeCallback(GLFWwindow* pWindow, int width, int height);

private:
    ZwWindowContainer* m_pWindowContainer = nullptr;
    ZwRender* m_pRender = nullptr;
};


#endif // !ZWAPP_H