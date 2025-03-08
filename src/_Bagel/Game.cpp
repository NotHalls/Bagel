#include <iostream>
#include <string>

#include "BagelInput.hpp"
#include "BagelMath.hpp"

#include "BagelTools.hpp"
#include "Renderer/Renderer.hpp"

#include "Game.hpp"

Game::Game() : Layer("Game"), m_CameraController(45.0f, 800.0f, 600.0f)
{
  m_boxTexture =
      Texture::Create("assets/Textures/Box.png", TextureType::Diffuse);
  // a default texture creation. we will have a white 1/1 pixel texture with
  // data (color) we spesified in the SetData()
  m_defaultTex = Texture::Create(1, 1);
  m_defaultTex->SetTextureType(TextureType::Diffuse);
  uint32_t whiteColor = 0xffffffff;
  m_defaultTex->SetData(&whiteColor, sizeof(uint32_t));
}

void Game::Start()
{
  // writing this code here just to test if i can write it here.
  // i could have wrote it in the Constructor but i decided to do it here
  // @FIXME: well the Default Plane model doesn't work correctly.
  m_Cube = Model::Create(DefaultModels::Cube, m_boxTexture);
  m_Light = Model::Create("assets/Models/Light.gltf");

  m_Light->GetTransform().Position = {0.0f, 5.0f, 0.0f};
  m_Cube->GetTransform().Scale = {10.0f, 0.1f, 10.0f};
}

void Game::Update(double deltaTime)
{
  RenderCommand::ColorScreen(m_screenColor);
  m_CameraController.OnUpdate((float)deltaTime);
  Renderer::StartScene(m_CameraController.GetCamera());
  {
    m_Cube->Draw();
    m_Light->Draw();
  }
  Renderer::EndScene();
}

void Game::ProcessEvent(Event &event) { m_CameraController.OnEvent(event); }

void Game::Destroy() {}