#include <iostream>
#include <string>

#include <glad/glad.h>

#include "BagelInput.hpp"
#include "BagelMath.hpp"

#include "BagelTools.hpp"

#include "Game.hpp"


Game::Game()
    : Component("Game"), m_CameraController(45.0f, 800.0f, 600.0f)
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

    m_CameraController.OnUpdate((float)deltaTime);
    Input::OnMouseMove(
        std::bind(&Game::onMouseMove, this, std::placeholders::_1, std::placeholders::_2));

    m_2DShader->Bind();

    glm::mat4 model = glm::mat4(1.0f);
    model =
        glm::translate(glm::mat4(1.0f), m_position) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::scale(glm::mat4(1.0f), m_scale
    );


    m_model->Draw(m_2DShader, m_CameraController.GetCamera(), model);
    m_backpack->Draw(m_2DShader, m_CameraController.GetCamera(), model);
    m_box->Draw(m_2DShader, m_CameraController.GetCamera(), model);
}

void Game::Destroy()
{}


// @TODO: This should be in the CameraController Class
void Game::onMouseMove(float x, float y)
{
    m_CameraController.OnMouseMove(x, y);
}