#ifndef ZWAPP_H
#define ZWAPP_H

class ZwWindow;
class ZwRender;
class ZwApp
{
public:
    void excute();

private:
    void mainLoop();
    void cleanUp();

private:
    ZwWindow* m_pWindow = nullptr;
    ZwRender* m_pRender = nullptr;
};


#endif // !ZWAPP_H