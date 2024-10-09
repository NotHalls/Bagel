#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>

#include <glad/glad.h>
#include <stdexcept>

#include "GLFW/glfw3.h"
#include "Renderer/_Renderer.hpp"
#include "App/Component.hpp"
#include "Tools/Time.hpp"
#include "Tools/Random.hpp"
#include "Debugger/defines.hpp"

#include "Game.hpp"


Game::Game()
    : Component("Game")
{
    m_2DShader = std::shared_ptr<Shader>(Shader::CreateShader({
        "assets/shaders/2DShader.vertex.glsl",
        "assets/shaders/2DShader.fragment.glsl"
    }));

    m_boxTexture = Texture::Create("assets/Textures/Box.png");
}

void Game::Start()
{}

void Game::Update(double deltaTime)
{
    Renderer::ColorScreen(m_screenColor);

    m_IndexBuffer = IndexBuffer::Create(indices, 6);

    /*
    
    */

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    m_boxTexture->Bind(0);

    m_2DShader->Bind();
    m_2DShader->SetUniformVec3("u_color", m_triColor);
    m_2DShader->SetUniformInt("u_texture", 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Game::Destroy()
{}