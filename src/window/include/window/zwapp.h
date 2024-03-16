#ifndef ZWAPP_H
#define ZWAPP_H

class ZwWindow;
class ZwApp
{
public:
    void excute();

private:
    void mainLoop();
    void cleanUp();

private:
    ZwWindow* m_pWindow = nullptr;
};


#endif // !ZWAPP_H