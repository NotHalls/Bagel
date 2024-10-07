#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>

#include <glad/glad.h>
#include <stdexcept>

#include "Renderer/_Renderer.hpp"
#include "App/Component.hpp"
#include "Tools/Time.hpp"
#include "Tools/Random.hpp"

#include "Game.hpp"


Game::Game()
    : Component("Game")
{
    m_2DShader = std::shared_ptr<Shader>(Shader::CreateShader({
        "assets/shaders/2DShader.vertex.glsl",
        "assets/shaders/2DShader.fragment.glsl"
    }));
}

void Game::Start()
{}

void Game::Update(double deltaTime)
{
    renderer.ColorScreen(m_screenColor);


    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);
    glGenVertexArrays(1, &m_VAO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    m_2DShader->Bind();
    m_2DShader->SetUniformVec3("u_color", m_triColor);


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Game::Destroy()
{}