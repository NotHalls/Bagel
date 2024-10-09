#pragma once

#include <cstdint>
#include <memory>

#include "ext/vector_float4.hpp"

#include "Renderer/_Renderer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/VertexArray.hpp"
#include "App/Component.hpp"
#include "Renderer/Texture.hpp"
#include "Game/Object.hpp"


 class Game : public Component
{
private:
    glm::vec4 m_screenColor = {0.1f, 0.1f, 0.1f, 1.0f};

    glm::vec3 m_triColor = {0.5f, 0.0f, 0.5f};


    // n *m where n is the number of vertices; m is the number of attributes
    float vertices[4 *8] = 
    {
        // positions                // color                // texCoordsw
        -0.5f,  -0.5f,  0.0f,       1.0f, 1.0f, 1.0f,       0.0f, 0.0f,
         0.5f,  -0.5f,  0.0f,       0.0f, 0.0f, 1.0f,       1.0f, 0.0f,
         0.5f,   0.5f,  0.0f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
        -0.5f,   0.5f,  0.0f,       0.0f, 1.0f, 0.0f,       0.0f, 1.0f
    };

    // n *3 where n = number of triangles
    uint32_t indices[2 *3] =
    {
        0, 1, 2,
        2, 3, 0
    };

    std::shared_ptr<VertexArray>
    m_VertexArray = VertexArray::Create();
    std::shared_ptr<VertexBuffer>
    m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));    
    std::shared_ptr<IndexBuffer>
    m_IndexBuffer; // @FIXME: why the fuck cant i initialize the index buffer here?

    std::shared_ptr<Texture> m_boxTexture;

    // std::shared_ptr<Object> m_boxObject("NAME", optional: texture, optional: color);

    std::shared_ptr<Shader> m_2DShader;


public:
    Game();
    virtual ~Game() = default;

    virtual void Start() override;
    virtual void Update(double deltaTime) override;
    virtual void Destroy() override;
};