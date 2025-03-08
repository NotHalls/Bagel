#include "Time.hpp"
#include <iostream>

std::chrono::time_point<std::chrono::high_resolution_clock> Time::startTime =
    Time::InitTime();
std::chrono::time_point<std::chrono::high_resolution_clock> Time::userStartTime;

bool Time::timerStarted = false;

std::chrono::time_point<std::chrono::high_resolution_clock> Time::InitTime()
{
  return std::chrono::high_resolution_clock::now();
}

// FUNCTIONALITIES //
double Time::GetElapsedTime()
{
  auto currentTime = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> timeElapsed = currentTime - startTime;
  return timeElapsed.count();
}

void Time::StartTimer()
{
  userStartTime = std::chrono::high_resolution_clock::now();
  timerStarted = true;
}

double Time::GetTimeStep()
{
  if(!timerStarted)
  {
    std::cerr << "Timer Not Initialized";
    return -1;
  }

  auto timeStep = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> timeElapsed = timeStep - userStartTime;
  return timeElapsed.count();
}