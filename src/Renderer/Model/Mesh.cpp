#include "Mesh.hpp"

#include <glad/glad.h>

#include "BagelTools.hpp"


std::shared_ptr<Mesh> Mesh::Create(
    const std::vector<ModelVertice>& vertices, const std::vector<uint32_t>& indices,
    const std::vector<ModelTexture>& textures
)
{ return std::make_shared<Mesh>(vertices, indices, textures); }


Mesh::Mesh(
    const std::vector<ModelVertice>& vertices, const std::vector<uint32_t>& indices,
    const std::vector<ModelTexture>& textures
)
    : m_vertices(vertices), m_Indices(indices), m_textures(textures)
{ init(); }

void Mesh::init()
{
    m_VAO = VertexArray::Create();
    m_IBO = IndexBuffer::Create(m_Indices.data(), sizeof(m_Indices) / sizeof(uint32_t));
    m_VBO = VertexBuffer::Create(
        reinterpret_cast<const float*>(m_vertices.data()),
        (m_vertices.size() * (sizeof(ModelVertice) / sizeof(float))) * sizeof(float)
    );

    m_VBO->SetBufferLayout({
        { AttribType::Vec3 },     // Positions
        { AttribType::Vec3 },     // Color
        { AttribType::Vec2 },     // TexCoords
        { AttribType::Vec3 }      // Normals
    });

    m_VAO->AddVertexBuffer(m_VBO);

    m_VAO->Unbind();
}

void Mesh::Draw(Shader& shader)
{
    uint32_t difuseCount = 1;
    uint32_t roughnessCount  = 1;
    uint32_t metallicCount = 1;
    uint32_t normalCount = 1;


    for(uint32_t i = 0; i < m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string textureTypeString = TextureTypeString(m_textures[i].Texture->GetTextureType());
        std::string textureNumberOffset;
        
        if(textureTypeString == "Diffuse")
            textureNumberOffset = std::to_string(difuseCount++);
        else if(textureTypeString == "Roughness")
            textureNumberOffset = std::to_string(roughnessCount++);
        else if(textureTypeString == "Metallic")
            textureNumberOffset = std::to_string(metallicCount++);
        else if(textureTypeString == "Normal")
            textureNumberOffset = std::to_string(normalCount++);
        else
            ASSERT(false, "Unknown Texture Type Found While Processing Data To Shader");

        shader.SetUniformInt("u_material." + textureTypeString + textureNumberOffset, i);
        m_textures[i].Texture->Bind(i);
    }
    glActiveTexture(GL_TEXTURE0);

    m_VAO->Bind();
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
    m_VAO->Unbind();
}