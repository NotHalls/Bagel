#include <iostream>
#include <string>

#include <glad/glad.h>

#include "BagelInput.hpp"
#include "BagelMath.hpp"

#include "BagelTools.hpp"
#include "Renderer/Renderer.hpp"

#include "Game.hpp"


Game::Game()
    : Component("Game"), m_CameraController(45.0f, 800.0f, 600.0f)
{
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
    RenderCommand::ColorScreen(m_screenColor);

    m_CameraController.OnUpdate((float)deltaTime);
    Input::OnMouseMove(
        std::bind(&Game::onMouseMove, this, std::placeholders::_1, std::placeholders::_2));

    glm::mat4 model = glm::mat4(1.0f);
    model =
        glm::translate(glm::mat4(1.0f), m_position) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::scale(glm::mat4(1.0f), m_scale
    );

    m_position.x = sin(Time::GetElapsedTime());

    Renderer::StartScene(m_CameraController.GetCamera());
    {
        m_model->Draw(model);
        m_backpack->Draw(model);
        m_box->Draw(model);
    }
    Renderer::EndScene();
}

void Game::Destroy()
{}


// @TODO: This should be in the CameraController Class
void Game::onMouseMove(float x, float y)
{
    m_CameraController.OnMouseMove(x, y);
}