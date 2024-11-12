#pragma once

#include <cstdint>
#include <memory>

#include "BagelMath.hpp"
#include "BagelEngine.hpp"
#include "BagelApp.hpp"

#include "Renderer/Model/Mesh.hpp"
#include "Renderer/Model/Model.hpp"

#include "Game/CameraController.hpp"


class Game : public Layer
{
private:
    glm::vec4 m_screenColor = {0.1f, 0.1f, 0.1f, 1.0f};

    CameraController m_CameraController;

    std::shared_ptr<Texture> m_boxTexture;

    std::shared_ptr<Model> m_model;
    std::shared_ptr<Model> m_backpack;

    std::shared_ptr<Model> m_box;


private:
    void onMouseMove(float x, float y);

public:
    Game();
    virtual ~Game() = default;

    virtual void Start() override;
    virtual void Update(double deltaTime) override;
    virtual void Destroy() override;
};