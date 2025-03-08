#include "Random.hpp"
#include <random>

std::mt19937 Random::m_generator = Random::Init();

std::mt19937 Random::Init()
{
  std::random_device rd;
  return std::mt19937(rd());
}

int Random::Int(int min, int max)
{
  std::uniform_int_distribution<> distribution(min, max);
  return distribution(m_generator);
}

float Random::Float(float min, float max)
{
  std::uniform_real_distribution<float> distribution(min, max);
  return distribution(m_generator);
}