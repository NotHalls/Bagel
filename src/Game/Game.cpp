#include <cstddef>
#include <iostream>

#include <glad/glad.h>
#include <stdexcept>

#include "Renderer/_Renderer.hpp"
#include "App/Object.hpp"

#include "Game.hpp"


Game::Game()
    : Object("Game")
{
    m_2DShader = std::shared_ptr<Shader>(Shader::CreateShader({
        "assets/shaders/2DShader.vertex.glsl",
        "assets/shaders/2DShader.fragment.glsl"
    }));
}

void Game::Start()
{
    std::cout << "STARTING..." << std::endl;
}

void Game::Update(float deltaTime)
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    m_2DShader->Bind();
    m_2DShader->SetUniformVec3("color", {1.0f, 0.0f, 1.0f});


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Game::Destroy()
{
}