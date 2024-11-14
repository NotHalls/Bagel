#include <iostream>
#include <string>

#include "BagelInput.hpp"
#include "BagelMath.hpp"

#include "BagelTools.hpp"
#include "Renderer/Renderer.hpp"

#include "Game.hpp"


Game::Game()
    : Layer("Game"), m_CameraController(45.0f, 800.0f, 600.0f)
{
    m_model = Model::Create("assets/models/Monkey/Monkey.fbx");
    m_backpack = Model::Create("assets/models/SurvivalBagpack/Survival_BackPack_2.fbx");

    m_boxTexture = Texture::Create("assets/Textures/Box.png", TextureType::Diffuse);

    // @TODO: create a DefaultModel with only color.
    // maybe we can add that when we have materials implemented
    m_box = Model::Create(DefaultModels::Cube, m_boxTexture);
}

void Game::Start()
{
    // WOW!!! THE PERFORMENCE IS... ASS PROBABLY
    // CURNT MODELS: 100 * 100 with 4 vertices (planes)
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            std::shared_ptr<Model> model = Model::Create(DefaultModels::Cube, m_boxTexture);
            model->GetTransform().Position = glm::vec3((float)i * 2.5f, (float)j * 2.5f, 0.0f);
            model->GetTransform().Rotation = glm::vec3(90.0f, 0.0f, 0.0f);

            m_WOW.push_back(model);
        }
    }
}

void Game::Update(double deltaTime)
{
    RenderCommand::ColorScreen(m_screenColor);

    m_CameraController.OnUpdate((float)deltaTime);

    m_model->GetTransform().Position = {sin(Time::GetElapsedTime()), 0.0f, 0.0f};
    m_backpack->GetTransform().Position = {sin(Time::GetElapsedTime()), 0.0f, 0.0f};
    m_box->GetTransform().Position = {sin(Time::GetElapsedTime()), 0.0f, 0.0f};

    Renderer::StartScene(m_CameraController.GetCamera());
    {
        // m_model->Draw();
        // m_backpack->Draw();
        // m_box->Draw();

        for(auto& wow : m_WOW)
        {
            wow->Draw();
        }
    }
    Renderer::EndScene();

    // std::cout << 1 / deltaTime << "\n";
}

void Game::ProcessEvent(Event& event)
{
    m_CameraController.OnEvent(event);
}

void Game::Destroy()
{}