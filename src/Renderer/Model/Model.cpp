// #include "Model.hpp"

// #include "BagelTools.hpp"


// std::unique_ptr<Model> Model::Create(const std::string& path)
// { return std::make_unique<Model>(path); }


// Model::Model(const std::string& path)
//     : m_path(path)
// { loadModel(path); }


// void Model::Draw(Shader& shader)
// {
//     for(Mesh& mesh : m_meshes)
//         mesh.Draw(shader);
// }


// void Model::loadModel(const std::string& path)
// {
//     Assimp::Importer importer;
//     const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate || aiProcess_FlipUVs);

//     ASSERT(scene, "Assimp's Scene Was Not Initialized");
//     ASSERT(!(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE),
//            "Assimp's Scene Flags Were Not Initialized");
//     ASSERT(scene->mRootNode, "Assimp's Root Node Was Not Found");

//     m_path = path.substr(0, path.find_last_of('/'));
//     processNodes(scene->mRootNode, scene);
// }

