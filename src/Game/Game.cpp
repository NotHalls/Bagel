#include <iostream>

#include "Renderer/_Renderer.hpp"
#include "App/Object.hpp"

#include "Game.hpp"


Game::Game()
    : Object("Game")
{}

void Game::Start()
{
    std::cout << "STARTING..." << std::endl;
}

void Game::Update(float deltaTime)
{
    renderer.ColorScreen(m_screenColor);
}