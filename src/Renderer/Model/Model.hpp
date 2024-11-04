#pragma once

#include <string>
#include <memory>

#include "BagelMath.hpp"

#include "Mesh.hpp"


// assimp stuff that i dont wanna include in this file
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;


enum class ModelImportSettings : uint32_t
{ // these correspond to aiProcess flags
    None                = 0,
    Triangulate         = 0x8,
    FlipUVs             = 0x800000,
    GenerateNormals     = 0x20,
    SplitLargeMeshes    = 0x80,
    OptimizeMeshes      = 0x200000
};


class Model
{
private:
    std::string m_modelDirectory;
    std::vector<Mesh> m_meshes;
    uint32_t m_modelImportSettings;


private:
    void loadModel(const std::string& modelPath);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture>> loadMaterialTexture(
        aiMaterial* material, TextureType textureTypeEnum);

public:
    Model(const std::string& modelPath, uint32_t importSettings);

    void Draw(
        const std::shared_ptr<Shader>& shader, const Camera& camera,
        const glm::mat4& modelMatrix);
    void SetImportSettings(uint32_t flags) { m_modelImportSettings = flags; }

    static std::shared_ptr<Model> Create(
        const std::string& modelPath,
        uint32_t importSettings = 
            static_cast<uint32_t>(ModelImportSettings::Triangulate) |
            static_cast<uint32_t>(ModelImportSettings::FlipUVs));
};