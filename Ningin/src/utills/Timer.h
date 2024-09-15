#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
    // Returns the delta time in seconds
    float GetDeltaTime();
    void ResetDeltaTime();

private:
    std::chrono::high_resolution_clock::time_point lastTime;
};