#include <iostream>
#include <string>

#include <glad/glad.h>

#include "BagelInput.hpp"
#include "BagelMath.hpp"

#include "BagelTools.hpp"

#include "Game.hpp"

Game::Game()
    : Component("Game")
{
    m_2DShader = std::shared_ptr<Shader>(Shader::CreateShader({
        "assets/shaders/2DShader.vertex.glsl",
        "assets/shaders/2DShader.fragment.glsl"
    }));

    m_boxTexture = Texture::Create("assets/Textures/Box.png");
    m_wedTexture = Texture::Create("assets/Textures/Wed.jpg");
}

void Game::Start()
{}

void Game::Update(double deltaTime)
{
    glEnable(GL_DEPTH_TEST);
    Renderer::ColorScreen(m_screenColor);

    m_IndexBuffer = IndexBuffer::Create(indices, 36);
    
    m_VertexBuffer->SetBufferLayout({
        { AttribType::Vec3 },   // position
        { AttribType::Vec3 },   // color
        { AttribType::Vec2 }    // texCoords
    });
    
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    m_model =
        glm::translate(glm::mat4(1.0f), m_position) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::scale(glm::mat4(1.0f), m_scale);

    m_view = glm::mat4(1.0f);
    m_view = glm::lookAt(m_cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    m_mvp = m_projection * m_view * m_model;

    m_boxTexture->Bind(0);
    m_wedTexture->Bind(1);

    m_2DShader->Bind();

    m_2DShader->SetUniformMat4("u_mvp", m_mvp);
    m_2DShader->SetUniformVec3("u_color", m_triColor);
    m_2DShader->SetUniformInt("u_texture", 0);
    m_2DShader->SetUniformInt("u_texture1", 1);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

void Game::Destroy()
{}