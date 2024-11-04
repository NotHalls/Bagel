#pragma once

#include <cstdint>
#include <memory>

#include "BagelMath.hpp"
#include "BagelGame.hpp"
#include "BagelEngine.hpp"
#include "BagelApp.hpp"

#include "Renderer/Model/Mesh.hpp"
#include "Renderer/Model/Model.hpp"


class Game : public Component
{
private:
    glm::vec4 m_screenColor = {0.1f, 0.1f, 0.1f, 1.0f};

    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_scale    = glm::vec3(1.0f, 1.0f, 1.0f);

    float mouseSensitivity = 0.1;
    float camSpeed = 5.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = (float)800/2, lastY = (float)600/2; // should be the window's width/2, height/2
    bool firstMouse = true;

    Camera m_camera;

    std::shared_ptr<Shader> m_2DShader;

    std::shared_ptr<Model> m_model;
    std::shared_ptr<Model> m_backpack;


private:
    void onMouseMove(float x, float y);
    void handleInput(double deltaTime);

public:
    Game();
    virtual ~Game() = default;

    virtual void Start() override;
    virtual void Update(double deltaTime) override;
    virtual void Destroy() override;
};