#include "Model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "stb_image.hpp"

#include "Tools/Debug.hpp"


// private to this file
aiTextureType GetAssimpTextureType(TextureType type)
{
    switch(type)
    {
        case TextureType::None:         return aiTextureType_NONE;
        case TextureType::Diffuse:      return aiTextureType_DIFFUSE;
        case TextureType::Roughness:    return aiTextureType_DIFFUSE_ROUGHNESS;
        case TextureType::Metallic:     return aiTextureType_METALNESS;
        case TextureType::Normal:       return aiTextureType_NORMALS;

        default: return aiTextureType_UNKNOWN;
    }
    return aiTextureType_UNKNOWN;
}


std::shared_ptr<Model> Model::Create(const std::string& modelPath, uint32_t importSettings)
{ return std::make_shared<Model>(modelPath, importSettings); }

// this is to create basic models
std::shared_ptr<Model> Model::Create(DefaultModels model,
    const std::shared_ptr<Texture>& texture,
    uint32_t importSettings)
{ return std::make_shared<Model>(model, texture, importSettings); }


Model::Model(const std::string& modelPath, uint32_t importSettings)
    : m_modelImportSettings(importSettings)
{
    m_modelDirectory = modelPath.substr(0, modelPath.find_last_of("/"));
    loadModel(modelPath);
}

// this is where we call the right functions to setup those basic meshes
Model::Model(DefaultModels model, const std::shared_ptr<Texture>& texture,
        uint32_t importSettings)
{
    switch(model)
    {
        case DefaultModels::Plane:  createPlane(importSettings, texture);
        case DefaultModels::Cube:   createCube(importSettings, texture);

        default: ASSERT(true, "The Selected Default Model Doesn't Exist");
    }

    ASSERT(true, "The Selected Default Model Doesn't Exist");
}

void Model::Draw(const glm::mat4& modelMatrix)
{
    for(Mesh mesh : m_meshes)
        mesh.Draw(modelMatrix);
}


void Model::loadModel(const std::string& modelPath)
{
    Assimp::Importer importer;
    // @BEFORE_COMMIT: does the importSettings work?
    const aiScene* scene = importer.ReadFile(modelPath,
        m_modelImportSettings |
        aiProcess_PreTransformVertices |
        aiProcess_GlobalScale);

    ASSERT(scene,
        "Failed To Initialize The Assimp Scene In Model: " + modelPath
        + "\n\tERROR: " + importer.GetErrorString() + "\n");
    ASSERT(!(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE),
        "Failed To Initialize Assimp Scene Flags In Model: " + modelPath
        + "\n\tERROR: " + importer.GetErrorString() + "\n");
    ASSERT(scene->mRootNode,
        "Failed To Find The Root Node In Model: " + modelPath
        + "\n\tERROR: " + importer.GetErrorString() + "\n");

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }

    for(uint32_t i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<ModelVertice> vertices;
    std::vector<uint32_t> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    // process vertices
    for(uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        ModelVertice vertice;

        glm::vec3 vertexPosition;
        vertexPosition.x = mesh->mVertices[i].x;
        vertexPosition.y = mesh->mVertices[i].y;
        vertexPosition.z = mesh->mVertices[i].z;
        vertice.Position = vertexPosition;

        glm::vec3 vertexNormal;
        vertexNormal.x = mesh->mNormals[i].x;
        vertexNormal.y = mesh->mNormals[i].y;
        vertexNormal.z = mesh->mNormals[i].z;
        vertice.Normals = vertexNormal;

        // @TODO: Add Colors From ASSIMP
        glm::vec3 vertexColor;
        vertexColor.x = 1.0f;
        vertexColor.y = 1.0f;
        vertexColor.z = 1.0f;
        vertice.Color = vertexColor;

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vertexTexCoord;
            vertexTexCoord.x = mesh->mTextureCoords[0][i].x;
            vertexTexCoord.y = mesh->mTextureCoords[0][i].y;
            vertice.TextureCoordinates = vertexTexCoord;
        }   
        else
            vertice.TextureCoordinates = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertice);
    }

    // process indices
    for(uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(uint32_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process textures
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<std::shared_ptr<Texture>> diffuseMaps =
            loadMaterialTexture(material, TextureType::Diffuse);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        
        std::vector<std::shared_ptr<Texture>> roughnessMaps =
            loadMaterialTexture(material, TextureType::Roughness);
        textures.insert(textures.end(), roughnessMaps.begin(), roughnessMaps.end());

        std::vector<std::shared_ptr<Texture>> metallicMaps =
            loadMaterialTexture(material, TextureType::Metallic);
        textures.insert(textures.end(),metallicMaps.begin(),metallicMaps.end());

        std::vector<std::shared_ptr<Texture>> normalMaps =
            loadMaterialTexture(material, TextureType::Normal);
        textures.insert(textures.end(),normalMaps.begin(),normalMaps.end());
    }

    return Mesh(vertices, indices, textures);
}


std::vector<std::shared_ptr<Texture>> Model::loadMaterialTexture(
    aiMaterial* material, TextureType textureTypeEnum)
{
    std::vector<std::shared_ptr<Texture>> textures;
    for(uint32_t i = 0; i < material->GetTextureCount(GetAssimpTextureType(textureTypeEnum)); i++)
    {
        aiString str;
        material->GetTexture(GetAssimpTextureType(textureTypeEnum), i, &str);

        std::shared_ptr<Texture> texture = 
        Texture::Create(m_modelDirectory + "/" + std::string(str.C_Str()), textureTypeEnum);
        textures.push_back(texture);
    }
    return textures;
}


void Model::createPlane(uint32_t importSettings,
    const std::shared_ptr<Texture>& texture)
{
    // @TODO: well we have a fixed amount for a plane so why not use std::array
    // i will do that later actually

    std::vector<ModelVertice> planeVertices;
    planeVertices.push_back(ModelVertice{
        { glm::vec3(-1.0f, 0.0f, -1.0f) },
        { glm::vec3( 1.0f, 1.0f,  1.0f) },
        { glm::vec2( 0.0f, 0.0f)        },
        { glm::vec3( 1.0f, 1.0f,  1.0f) }
    });
    planeVertices.push_back(ModelVertice{
        { glm::vec3(1.0f,  0.0f, -1.0f) },
        { glm::vec3(1.0f,  1.0f,  1.0f) },
        { glm::vec2(1.0f,  0.0f)        },
        { glm::vec3(1.0f,  1.0f,  1.0f) }
    });
    planeVertices.push_back(ModelVertice{
        { glm::vec3(-1.0f, 0.0f,  1.0f) },
        { glm::vec3( 1.0f, 1.0f,  1.0f) },
        { glm::vec2( 0.0f, 1.0f)        },
        { glm::vec3( 1.0f, 1.0f,  1.0f) }
    });
    planeVertices.push_back(ModelVertice{
        { glm::vec3(1.0f, 0.0f,  1.0f) },
        { glm::vec3(1.0f, 1.0f,  1.0f) },
        { glm::vec2(1.0f, 1.0f)        },
        { glm::vec3(1.0f, 1.0f,  1.0f) }
    });

    std::vector<uint32_t> planeIndices;
    planeIndices.insert(planeIndices.end(), {
        0, 1, 2,
        2, 3, 1
    });

    std::vector<std::shared_ptr<Texture>> planeTextures;
    planeTextures.push_back(texture);

    Mesh mesh(planeVertices, planeIndices, planeTextures);
    m_meshes.push_back(mesh);
}

void Model::createCube(uint32_t importSettings,
    const std::shared_ptr<Texture>& texture)
{
    
}