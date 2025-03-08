#pragma once

#include <cstdint>
#include <memory>

#include "BagelApp.hpp"
#include "BagelEngine.hpp"
#include "BagelInput.hpp"
#include "BagelMath.hpp"

#include "Renderer/Model/Mesh.hpp"
#include "Renderer/Model/Model.hpp"

#include "Engine/CameraController.hpp"

class Game : public Layer
{
private:
  glm::vec4 m_screenColor = {0.1f, 0.1f, 0.1f, 1.0f};

  CameraController m_CameraController;

  std::shared_ptr<Texture> m_boxTexture;
  std::shared_ptr<Texture> m_defaultTex;

  std::shared_ptr<Model> m_model;
  std::shared_ptr<Model> m_backpack;

  std::shared_ptr<Model> m_box;

  std::shared_ptr<Model> m_testCube;

  // TESTING
  std::vector<std::shared_ptr<Model>> m_WOW;

public:
  Game();
  virtual ~Game() = default;

  virtual void Start() override;
  virtual void Update(double deltaTime) override;
  virtual void ProcessEvent(Event &event) override;
  virtual void Destroy() override;
};