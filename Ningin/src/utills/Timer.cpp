#include "Timer.h"

Timer::Timer() : lastTime(std::chrono::high_resolution_clock::now()) {}

float Timer::GetDeltaTime() 
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta = currentTime - lastTime;
    return delta.count();
}

void Timer::ResetDeltaTime() 
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    lastTime = currentTime;
}
