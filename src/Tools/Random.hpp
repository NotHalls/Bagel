#pragma once

#include <random>

class Random
{
private:
  static std::mt19937 m_generator;

private:
  static std::mt19937 Init();

public:
  static int Int(int min = 0, int max = 100);
  static float Float(float min = 0.0f, float max = 1.0f);
};