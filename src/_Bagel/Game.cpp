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

    m_model = Model::Create("assets/models/Monkey/Monkey.fbx");
    m_backpack = Model::Create("assets/models/SurvivalBagpack/Survival_BackPack_2.fbx");

    m_boxTexture = Texture::Create("assets/Textures/Box.png", TextureType::Diffuse);

    // @TODO: create a DefaultModel with only color.
    // maybe we can add that when we have materials implemented
    m_box = Model::Create(DefaultModels::Plane, m_boxTexture);
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


    m_model->Draw(m_2DShader, m_camera, model);
    m_backpack->Draw(m_2DShader, m_camera, model);
    m_box->Draw(m_2DShader, m_camera, model);
}

void Game::Destroy()
{}


// @TODO: This should be in the CameraController Class
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