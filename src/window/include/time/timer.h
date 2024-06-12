#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class Timer
{
public:
    Timer();
    void startFrame();
    double getFps() const { return m_fps; }


private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;
    int m_frameCount{ 0 };
    double m_fps = {.0};
};

#endif // !TIMER_H
