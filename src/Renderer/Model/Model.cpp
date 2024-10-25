#include "Model.hpp"


std::unique_ptr<Model> Model::Create(const std::string& path)
{ return std::make_unique<Model>(path); }


Model::Model(const std::string& path)
{
    // DO SOME ASSIMP THINGS
    // or make your own .obj importer
}