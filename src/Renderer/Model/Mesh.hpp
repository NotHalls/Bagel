#pragma once

#include "BagelMath.hpp"
#include "BagelEngine.hpp"
#include "Renderer/Camera.hpp"


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

    glm::mat4 m_modelMatrix;


private:
    void init();

public:
    Mesh(const std::vector<ModelVertice>& vertices, const std::vector<uint32_t>& indices,
         const std::vector<std::shared_ptr<Texture>>& textures);

    void Draw(const glm::mat4& modelMatrix);

    void SetModelMatrix(const glm::mat4& modelMat) { m_modelMatrix = modelMat; }
    const glm::mat4& GetModelMatrix() const { return m_modelMatrix; }

    static std::shared_ptr<Mesh> Create(
        const std::vector<ModelVertice>& vertices, const std::vector<uint32_t>& indices,
        const std::vector<std::shared_ptr<Texture>>& textures);
};