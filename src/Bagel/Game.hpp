#pragma once

#include <cstdint>
#include <memory>

#include "ext/vector_float3.hpp"
#include "ext/vector_float4.hpp"
#include "ext/matrix_float4x4.hpp"

#include "Renderer/Shader.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/VertexArray.hpp"
#include "App/Component.hpp"
#include "Renderer/Texture.hpp"


 class Game : public Component
{
private:
    glm::vec4 m_screenColor = {0.1f, 0.1f, 0.1f, 1.0f};

    glm::vec3 m_triColor = {0.5f, 0.0f, 0.5f};

    glm::mat4 m_mvp = glm::mat4(1.0f);
    glm::mat4 m_transform = glm::mat4(1.0f);
    glm::mat4 m_view = glm::mat4{1.0f};
    glm::mat4 m_projection = glm::mat4(1.0f);

    glm::vec3 m_position = {0.0f, 0.0f, -2.0f};
    glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};
    glm::vec3 m_rotation = {0.0f, 0.0f, 0.0f};

    float m_startTime;


    // n * m where n is the number of vertices; m is the number of attributes
    float vertices[8 * 8] = 
    {
        // positions                // color                // texCoordsw
        -0.5f,  -0.5f,  -0.5f,       1.0f, 1.0f, 1.0f,       0.0f, 0.0f,    //0
         0.5f,  -0.5f,  -0.5f,       0.0f, 0.0f, 1.0f,       1.0f, 0.0f,    //1
         0.5f,   0.5f,  -0.5f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,    //2
        -0.5f,   0.5f,  -0.5f,       0.0f, 1.0f, 0.0f,       0.0f, 1.0f,    //3

        -0.5f,  -0.5f,   0.5f,       1.0f, 1.0f, 1.0f,       0.0f, 0.0f,    //4
         0.5f,  -0.5f,   0.5f,       0.0f, 0.0f, 1.0f,       1.0f, 0.0f,    //5
         0.5f,   0.5f,   0.5f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,    //6
        -0.5f,   0.5f,   0.5f,       0.0f, 1.0f, 0.0f,       0.0f, 1.0f     //7
    };

    // n * 3 where n = number of triangles
    uint32_t indices[12 * 3] =
    {
        0, 1, 2, // front
        2, 3, 0,

        0, 4, 5, // down
        5, 1, 0,

        4, 5, 6, // back
        6, 7, 4,

        0, 7, 6, // top
        6, 1, 0,

        0, 3, 7, // left
        7, 4, 0,

        1, 5, 6, // right
        6, 2, 1,
    };

    std::shared_ptr<VertexArray>
    m_VertexArray = VertexArray::Create();
    std::shared_ptr<VertexBuffer>
    m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));    
    std::shared_ptr<IndexBuffer>
    m_IndexBuffer; // @FIXME: why the fuck cant i initialize the index buffer here?

    std::shared_ptr<Texture> m_boxTexture;
    std::shared_ptr<Texture> m_wedTexture;

    // std::shared_ptr<Object> m_boxObject("NAME", optional: texture, optional: color);

    std::shared_ptr<Shader> m_2DShader;


public:
    Game();
    virtual ~Game() = default;

    virtual void Start() override;
    virtual void Update(double deltaTime) override;
    virtual void Destroy() override;
};