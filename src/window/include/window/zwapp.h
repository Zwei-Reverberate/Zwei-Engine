#ifndef ZWAPP_H
#define ZWAPP_H
#include <qapplication.h>
#include <include/scene/scene.h>

class GLFWwindow;
class ZwMainWindow;
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
    void loadQss();
    static void framebufferResizeCallback(GLFWwindow* pWindow, int width, int height);

private:
    ZwMainWindow* m_pMainWindow = nullptr;
    ZwRender* m_pRender = nullptr;
    Scene* m_pScene = nullptr;
};


#endif // !ZWAPP_H