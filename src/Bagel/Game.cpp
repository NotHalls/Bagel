#include <string>

#include <glad/glad.h>

#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_float4x4.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/vector_float3.hpp"
#include "trigonometric.hpp"

#include "Renderer/Buffer.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/_Renderer.hpp"
#include "App/Component.hpp"
#include "Renderer/BufferLayout.hpp"
#include "Tools/Time.hpp"

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
{
    Time::StartTimer();
    m_startTime = Time::GetElapsedTime();
}

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

    m_transform = glm::rotate(
        m_transform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)
    );
    m_transform = glm::rotate(
        m_transform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)
    );
    m_transform = glm::rotate(
        m_transform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)
    );

    m_view = glm::mat4(1.0f);
    m_view = glm::translate(glm::mat4(1.0f), m_position);
    m_projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    m_mvp = m_projection * m_view * m_transform;

    float timeNow = Time::GetElapsedTime();
    if(timeNow - m_startTime >= (float)1 / (float)60)
    {
        m_rotation.y = 50.0f * deltaTime;
        m_startTime = timeNow;
    }

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