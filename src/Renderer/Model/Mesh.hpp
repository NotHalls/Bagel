#pragma once

#include "BagelMath.hpp"
#include "BagelEngine.hpp"


struct ModelVertice
{
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 TextureCoordinates;
    glm::vec3 Normals;
};


class Mesh
{
private:
    std::vector<ModelVertice> m_vertices;
    std::vector<uint32_t> m_Indices;
    std::vector<std::shared_ptr<Texture>> m_textures;

    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;


private:
    void init();

public:
    Mesh(const std::vector<ModelVertice>& vertices, const std::vector<uint32_t>& indices,
         const std::vector<std::shared_ptr<Texture>>& textures);

    void Draw(std::shared_ptr<Shader>& shader);

    // uint32_t GetVAO() { return m_VAO; }
    // uint32_t GetVBO() { return m_VBO; }
    // uint32_t GetIBO() { return m_IBO; }


    static std::shared_ptr<Mesh> Create(
        const std::vector<ModelVertice>& vertices, const std::vector<uint32_t>& indices,
        const std::vector<std::shared_ptr<Texture>>& textures);
};