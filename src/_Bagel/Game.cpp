#include <iostream>
#include <string>

#include <glad/glad.h>

#include "BagelInput.hpp"
#include "BagelMath.hpp"

#include "BagelTools.hpp"

#include "Game.hpp"


Game::Game()
    : Component("Game"), m_camera(45.0f, 800.0f, 600.0f)
{
    m_2DShader = std::shared_ptr<Shader>(Shader::CreateShader({
        "assets/shaders/2DShader.vertex.glsl",
        "assets/shaders/2DShader.fragment.glsl"
    }));

    // m_boxTexture = Texture::Create("assets/Textures/Box.png");
    m_boxTexture = Texture::Create("assets/Textures/Box.png", TextureType::Diffuse);
    m_wedTexture = Texture::Create("assets/Textures/Wed.jpg");

    m_model = Model::Create("assets/models/Monkey/Monkey.fbx");

    m_vertices.push_back(ModelVertice{
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    });

    m_vertices.push_back(ModelVertice{
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    });

    m_vertices.push_back(ModelVertice{
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    });

    m_vertices.push_back(ModelVertice{
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    });

    m_vertices.push_back(ModelVertice{
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    });

    m_vertices.push_back(ModelVertice{
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    });

    m_vertices.push_back(ModelVertice{
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    });

    m_vertices.push_back(ModelVertice{
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    });

    m_indices.insert(m_indices.end(), {
        0, 1, 2, 2, 3, 0,   // front
        0, 4, 5, 5, 1, 0,   // down
        4, 5, 6, 6, 7, 4,   // back
        3, 2, 6, 6, 7, 3,   // top
        0, 3, 7, 7, 4, 0,   //left
        1, 5, 6, 6, 2, 1    //right
    });
    

    m_textures.push_back(m_boxTexture);

    Texture m_sBoxTexture("assets/Textures/Box.png", TextureType::Diffuse);
    m_sTextures.push_back(m_sBoxTexture);
}

void Game::Start()
{}

void Game::Update(double deltaTime)
{
    glEnable(GL_DEPTH_TEST);
    Renderer::ColorScreen(m_screenColor);

    handleInput(deltaTime);
    Input::OnMouseMove(
        std::bind(&Game::onMouseMove, this, std::placeholders::_1, std::placeholders::_2));

    m_2DShader->Bind();

    glm::mat4 model = glm::mat4(1.0f);

    model =
        glm::translate(glm::mat4(1.0f), m_position) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::scale(glm::mat4(1.0f), m_scale);

    // Mesh boxMesh(m_vertices, m_indices, m_textures);
    // boxMesh.SetModelMatrix(model);
    // boxMesh.Draw(m_2DShader, m_camera, model);

    // m_model = Model::Create("assets/models/cat.gltf");
    // m_model->Draw(m_2DShader, m_camera);

    m_model->Draw(m_2DShader, m_camera, model);
}

void Game::Destroy()
{}


void Game::onMouseMove(float x, float y)
{
    if(firstMouse)
    {
        lastX = x;
        lastY = y;

        firstMouse = false;
    }

    float xOffset = x - lastX;
    float yOffset = lastY - y;
    lastX = x;
    lastY = y;

    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;


    if(pitch > 89.0f)
        pitch = 89.0f;
    else if(pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 dir = glm::vec3(0.0f);
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_camera.SetLookingTarget(dir);
}

void Game::handleInput(double deltaTime)
{
    glm::vec3 camPosition = m_camera.GetPosition();
    if(Input::IsKeyClicked(BG_KEY_W))
        camPosition += m_camera.GetLookingTarget() * camSpeed * (float)deltaTime;
    if(Input::IsKeyClicked(BG_KEY_S))
        camPosition -= m_camera.GetLookingTarget() * camSpeed * (float)deltaTime;
    if(Input::IsKeyClicked(BG_KEY_A))
        camPosition -= glm::normalize(glm::cross(
            m_camera.GetLookingTarget(), {0.0f, 1.0f, 0.0f})) * camSpeed * (float)deltaTime;
    if(Input::IsKeyClicked(BG_KEY_D))
        camPosition += glm::normalize(glm::cross(
            m_camera.GetLookingTarget(), {0.0f, 1.0f, 0.0f})) * camSpeed * (float)deltaTime;
    m_camera.SetPosition(camPosition);

    if(Input::IsKeyClicked(BG_KEY_C))
        Input::SetCursorMode(BG_CURSOR_MODE_DISABLED);
}