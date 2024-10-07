#pragma once

#include <chrono>


class Time
{
private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    static std::chrono::time_point<std::chrono::high_resolution_clock> userStartTime;

    static bool timerStarted;


private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> InitTime();

public:
    static double GetElapsedTime();

    static void StartTimer();
    static double GetTimeStep();
};