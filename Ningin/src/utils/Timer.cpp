#include "Timer.h"
#include <limits>

Timer::Timer() : lastTime(std::chrono::high_resolution_clock::now()) {}

float Timer::GetDeltaTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta = currentTime - lastTime;
    float deltaTime = delta.count();
    if (deltaTime == 0)
    {
        deltaTime = std::numeric_limits<float>::min();
    }
    return deltaTime;
}

void Timer::ResetDeltaTime() 
{
    lastTime = std::chrono::high_resolution_clock::now();
}
