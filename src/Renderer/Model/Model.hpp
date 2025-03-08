#pragma once

#include <memory>
#include <string>

#include "BagelMath.hpp"

#include "Mesh.hpp"

// assimp stuff that i dont wanna include in this file
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

enum class ModelImportSettings : uint32_t
{ // these correspond to aiProcess flags
  None = 0,
  Triangulate = 0x8,
  FlipUVs = 0x800000,
  GenerateNormals = 0x20,
  SplitLargeMeshes = 0x80,
  OptimizeMeshes = 0x200000
};

enum class DefaultModels
{
  Plane = 0,
  Cube = 1
};

class Model
{
private:
  std::string m_modelDirectory;
  std::vector<Mesh> m_meshes;
  uint32_t m_modelImportSettings;

public:
  // should probably have an component system for these kind of stuff
  // but this project is about learning rendering
  // not anything else i gotta remember that
  struct Transform
  {
    glm::vec3 Position = glm::vec3(0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f);
    glm::vec3 Scale = glm::vec3(1.0f);
  };

private:
  Transform m_transform;

private:
  void loadModel(const std::string &modelPath);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<std::shared_ptr<Texture>> loadMaterialTexture(
      aiMaterial *material, TextureType textureTypeEnum);

  void createPlane(uint32_t importSettings,
                   const std::shared_ptr<Texture> &texture);
  void createCube(uint32_t importSettings,
                  const std::shared_ptr<Texture> &texture);

public:
  Model(const std::string &modelPath, uint32_t importSettings);
  Model(DefaultModels model, const std::shared_ptr<Texture> &texture,
        uint32_t importSettings);

  // same comment i wrote while declaring transform variables
  Transform &GetTransform() { return m_transform; }
  const Transform &GetTransform() const { return m_transform; }
  void SetTransform(const Transform &transform) { m_transform = transform; }

  void Draw();
  void SetImportSettings(uint32_t flags) { m_modelImportSettings = flags; }

  static std::shared_ptr<Model> Create(
      const std::string &modelPath,
      uint32_t importSettings =
          static_cast<uint32_t>(ModelImportSettings::Triangulate) |
          static_cast<uint32_t>(ModelImportSettings::FlipUVs));

  static std::shared_ptr<Model> Create(
      DefaultModels model, const std::shared_ptr<Texture> &texture,
      uint32_t importSettings =
          static_cast<uint32_t>(ModelImportSettings::Triangulate) |
          static_cast<uint32_t>(ModelImportSettings::FlipUVs));
};