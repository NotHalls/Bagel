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
    m_box = Model::Create(DefaultModels::Plane, m_boxTexture);
}

void Game::Start()
{}

void Game::Update(double deltaTime)
{
    RenderCommand::ColorScreen(m_screenColor);

    m_CameraController.OnUpdate((float)deltaTime);

    m_model->GetTransform().Position = {sin(Time::GetElapsedTime()), 0.0f, 0.0f};
    m_backpack->GetTransform().Position = {sin(Time::GetElapsedTime()), 0.0f, 0.0f};
    m_box->GetTransform().Position = {sin(Time::GetElapsedTime()), 0.0f, 0.0f};

    Renderer::StartScene(m_CameraController.GetCamera());
    {
        m_model->Draw();
        m_backpack->Draw();
        m_box->Draw();
    }
    Renderer::EndScene();
}

void Game::ProcessEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseMoveEvent>(BIND_EVENT(Game::onMouseMove));
}

void Game::Destroy()
{}


bool Game::onMouseMove(MouseMoveEvent& mouseMoveEvent)
{
    std::cout << mouseMoveEvent.ToString() << "\n";
    m_CameraController.OnMouseMove(mouseMoveEvent.GetMouseAxis());

    return false;
}