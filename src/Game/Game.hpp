#pragma once

#include <cstdint>
#include <memory>

#include "ext/vector_float4.hpp"

#include "Renderer/_Renderer.hpp"
#include "Renderer/Shader.hpp"
#include "App/Object.hpp"


class Game : public Object
{
private:
    Renderer renderer;
    glm::vec4 m_screenColor = {0.1f, 0.1f, 0.1f, 1.0f};

    uint32_t m_VBO;
    uint32_t m_IBO;
    uint32_t m_VAO;

    // n *3 where n is the number of vertices
    float vertices[4 *3] = 
    {
        -0.5f,  -0.5f,  0.0f,
         0.5f,  -0.5f,  0.0f,
         0.5f,   0.5f,  0.0f,
        -0.5f,   0.5f,  0.0f
    };

    // n *3 where n = number of triangles
    uint32_t indices[2 *3] =
    {
        0, 1, 2,
        2, 3, 0
    };


    std::shared_ptr<Shader> m_2DShader;


public:
    Game();
    virtual ~Game() = default;

    virtual void Start() override;
    virtual void Update(float deltaTime) override;
    virtual void Destroy() override;
};