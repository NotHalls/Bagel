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

    glm::vec3 m_triColor = {0.5f, 0.0f, 0.5f};

    glm::mat4 m_mvp = glm::mat4(1.0f);
    glm::mat4 m_model = glm::mat4(1.0f);

    glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};
    glm::vec3 m_rotation = {0.0f, 0.0f, 0.0f};


    float mouseSensitivity = 0.1;
    float camSpeed = 5.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = (float)800/2, lastY = (float)600/2; // should be the window's width/2, height/2
    bool firstMouse = true;


    // n * m where n is the number of vertices; m is the number of attributes
    float vertices[8 * 11] = {
        // positions                 // color                // texCoordsw      // normals
        -0.5f,  -0.5f,  -0.5f,       1.0f, 1.0f, 1.0f,       0.0f, 0.0f,        1.0f, 1.0f, 1.0f,   // 0
         0.5f,  -0.5f,  -0.5f,       0.0f, 0.0f, 1.0f,       1.0f, 0.0f,        1.0f, 1.0f, 1.0f,   // 1
         0.5f,   0.5f,  -0.5f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,        1.0f, 1.0f, 1.0f,   // 2
        -0.5f,   0.5f,  -0.5f,       0.0f, 1.0f, 0.0f,       0.0f, 1.0f,        1.0f, 1.0f, 1.0f,   // 3

        -0.5f,  -0.5f,   0.5f,       1.0f, 1.0f, 1.0f,       0.0f, 0.0f,        1.0f, 1.0f, 1.0f,   // 4
         0.5f,  -0.5f,   0.5f,       0.0f, 0.0f, 1.0f,       1.0f, 0.0f,        1.0f, 1.0f, 1.0f,   // 5
         0.5f,   0.5f,   0.5f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,        1.0f, 1.0f, 1.0f,   // 6
        -0.5f,   0.5f,   0.5f,       0.0f, 1.0f, 0.0f,       0.0f, 1.0f,        1.0f, 1.0f, 1.0f,   // 7
    };

    // n * 3 where n = number of triangles
    uint32_t indices[12 * 3] = {
        0, 1, 2, // front
        2, 3, 0,

        0, 4, 5, // down
        5, 1, 0,

        4, 5, 6, // back
        6, 7, 4,

        3, 2, 6, // top
        6, 7, 3,

        0, 3, 7, // left
        7, 4, 0,

        1, 5, 6, // right
        6, 2, 1,
    };

    std::vector<ModelVertice> m_vertices;
    std::vector<uint32_t> m_indices;
    std::vector<std::shared_ptr<Texture>> m_textures;

    // ModelVertice m_verti[8] = {
    //     ModelVertice{glm::vec3(0.5f,   0.5f,  -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
    //     glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

    //     ModelVertice{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
    //     glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

    //     ModelVertice{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
    //     glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

    //     ModelVertice{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
    //     glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

    //     ModelVertice{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
    //     glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

    //     ModelVertice{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
    //     glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

    //     ModelVertice{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
    //     glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

    //     ModelVertice{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
    //     glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)}
    // };

    Camera m_camera;

    std::shared_ptr<VertexArray>
    m_VertexArray = VertexArray::Create();
    std::shared_ptr<VertexBuffer>
    m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    std::shared_ptr<IndexBuffer>
    m_IndexBuffer; // @FIXME: why the fuck cant i initialize the index buffer here?

    std::shared_ptr<Texture> m_boxTexture;
    std::shared_ptr<Texture> m_wedTexture;

    // std::shared_ptr<Object> m_boxObject("NAME", optional: texture, optional: color);
    // std::shared_ptr<Mesh> m_boxMesh = Mesh::Create(m_vertices, m_indices, m_textures);

    std::shared_ptr<Shader> m_2DShader;


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