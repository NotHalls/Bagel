// #pragma once

// #include <memory>
// #include <string>

// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

// #include "BagelEngine.hpp"
// #include "Renderer/Model/Mesh.hpp"


// class Model
// {
// private:
//     std::string m_path;
//     std::vector<Mesh> m_meshes;


// private:
//     void loadModel(const std::string& path);
//     void processNodes(aiNode* node, const aiScene* scene);
//     Mesh processMesh(aiMesh* mesh, const aiScene* scene);
//     std::vector<std::shared_ptr<Texture>> processMaterials(
//         aiMaterial* material,
//         aiTextureType textureType, const std::string& textureTypeString
//     );

// public:
//     Model() {}
//     Model(const std::string& path);

//     void Draw(Shader& shader);

//     static std::unique_ptr<Model> Create(const std::string& path);
// };