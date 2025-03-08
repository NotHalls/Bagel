#pragma once

#include <memory>

#include "BagelMath.hpp"
#include "Renderer/Texture.hpp"

class Material
{
public:
  // textures
  std::shared_ptr<Texture> DiffuseMap;
  std::shared_ptr<Texture> RoughnessMap;
  std::shared_ptr<Texture> MetallicMap;
  std::shared_ptr<Texture> NormalMap;

  // material properties
  glm::vec3 Color;

private:
  void initDefaults();

public:
  Material();
  Material(std::shared_ptr<Texture> diffTex, std::shared_ptr<Texture> roughTex,
           std::shared_ptr<Texture> metTex, std::shared_ptr<Texture> normalTex);

  static std::shared_ptr<Material> Create(
      std::shared_ptr<Texture> diffTex,
      std::shared_ptr<Texture> roughTex = nullptr,
      std::shared_ptr<Texture> metTex = nullptr,
      std::shared_ptr<Texture> normalTex = nullptr);
  static std::shared_ptr<Material> Create();
};