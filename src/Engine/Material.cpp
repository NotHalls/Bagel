#include "Material.hpp"


std::shared_ptr<Material> Material::Create()
{ return std::make_shared<Material>(); }
std::shared_ptr<Material> Material::Create(
    std::shared_ptr<Texture> diffTex,
    std::shared_ptr<Texture> roughTex,
    std::shared_ptr<Texture> metTex,
    std::shared_ptr<Texture> normalTex
)
{ return std::make_shared<Material>(diffTex, roughTex, metTex, normalTex); }

Material::Material()
    : Color(1.0f, 1.0f, 1.0f)
{ initDefaults(); }
Material::Material(
    std::shared_ptr<Texture> diffTex,
    std::shared_ptr<Texture> roughTex,
    std::shared_ptr<Texture> metTex,
    std::shared_ptr<Texture> normalTex
)
    : DiffuseMap(diffTex),
      RoughnessMap(roughTex),
      MetallicMap(metTex),
      NormalMap(normalTex),
      Color(1.0f, 1.0f, 1.0f)
{}


void Material::initDefaults()
{
    // for diffTex we will make a 1x1 pixel texture with white color.
    

    // @TEST: is it good to make these nullptr or just a white texture?
    RoughnessMap = nullptr;
    MetallicMap = nullptr;
    NormalMap = nullptr;
}