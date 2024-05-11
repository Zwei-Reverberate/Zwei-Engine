#ifndef ZWAPP_H
#define ZWAPP_H

class GLFWwindow;
class ZwWindow;
class ZwRender;
class ZwApp
{
public:
    void excute();

private:
    void mainLoop();
    void cleanUp();
    void registerFrameBufferCallback();
    static void framebufferResizeCallback(GLFWwindow* pWindow, int width, int height);

private:
    ZwWindow* m_pWindow = nullptr;
    ZwRender* m_pRender = nullptr;
};


#endif // !ZWAPP_H