#include <include/time/timer.h>

Timer::Timer()
{
	m_lastTime = std::chrono::high_resolution_clock::now();
}

void Timer::startFrame()
{
    m_frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = currentTime - m_lastTime;

    if (elapsed.count() >= 1.0) 
    {
        m_fps = m_frameCount / elapsed.count();
        m_frameCount = 0;
        m_lastTime = currentTime;
    }
}

