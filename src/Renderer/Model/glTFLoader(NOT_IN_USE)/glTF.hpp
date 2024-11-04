#pragma once

#include <string>
#include <vector>
#include <memory>

#include <json.hpp>

#include "BagelEngine.hpp"
#include "BagelMath.hpp"

#include "Renderer/Camera.hpp"
#include "Renderer/Model/Mesh.hpp"


using json = nlohmann::json;


class glTFModel
{
private:
    std::string m_filePath;
    std::vector<unsigned char> m_data;
    json m_JSON;

    std::vector<Mesh> m_meshes;
    std::vector<std::shared_ptr<Texture>> m_loadedTextures;
    std::vector<std::string> m_loadedTextureNames;

    std::vector<glm::vec3> m_positions;
    std::vector<glm::quat> m_rotations;
    std::vector<glm::vec3> m_scales;
    std::vector<glm::mat4> m_modelMatrices;


private:
    std::string readFile(const std::string& path);
    std::vector<unsigned char> getData();

    std::vector<float> getFloats(json accessor);
    std::vector<uint32_t> getIndices(json accessor);
    std::vector<std::shared_ptr<Texture>> getTextures();

    std::vector<Mesh> loadMeshes(uint32_t meshIndex);
    void treverseNode(uint32_t node, glm::mat4 matrix = glm::mat4(1.0f));

    template<typename T, uint32_t N>
    std::vector<T> groupVec(const std::vector<float>& values);
    
    std::vector<ModelVertice> groupVertices(
        const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec2>& texCoords,
        const std::vector<glm::vec3>& normals);

public:
    glTFModel(const std::string& path);

    void Draw(std::shared_ptr<Shader>& shader, Camera& camera);


    static std::shared_ptr<glTFModel> Create(const std::string& modelPath);
};