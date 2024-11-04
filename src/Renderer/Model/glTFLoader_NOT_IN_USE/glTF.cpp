#include "glTF.hpp"

#include <fstream>
#include <sstream>

#include "BagelTools.hpp"


std::shared_ptr<glTFModel> glTFModel::Create(const std::string& modelPath)
{ return std::make_shared<glTFModel>(modelPath); }

glTFModel::glTFModel(const std::string& path)
    : m_filePath(path)
{ 
    std::string modelSource = readFile(path);
    m_JSON = nlohmann::json::parse(modelSource);

    // the data is basicly the bin file (.gltf) into a set of chars
    // representing all the bytes in the model bin file
    m_data = getData();

    treverseNode(0);
}

void glTFModel::Draw(std::shared_ptr<Shader>& shader, Camera& camera)
{
    // uint32_t iterator = 0;
    // for(Mesh mesh : m_meshes)
    // {
    //     mesh.SetModelMatrix(m_modelMatrices[iterator]);
    //     mesh.Draw(shader, camera);
    //     iterator++;
    // }

    for(uint32_t i = 0; i < m_meshes.size(); i ++)
    {
        m_meshes[i].SetModelMatrix(m_modelMatrices[i]); // choose one to use man
        m_meshes[i].Draw(shader, camera, m_modelMatrices[i]);
    }
}

void glTFModel::treverseNode(uint32_t node, glm::mat4 nodeMatrix)
{
    json currentNode = m_JSON["nodes"][node];

    glm::vec3 position = glm::vec3(0.0f);
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::mat4 matrix = glm::mat4(1.0f);

    if(currentNode.find("translation") != currentNode.end())
        for(uint32_t i = 0; i < currentNode["translation"].size(); i++)
            position[i] = (currentNode["translation"][i]);

    if(currentNode.find("rotation") != currentNode.end())
    {
        rotation[0] = currentNode["rotation"][3];
        rotation[1] = currentNode["rotation"][0];
        rotation[2] = currentNode["rotation"][1];
        rotation[3] = currentNode["rotation"][2];
    }

    if(currentNode.find("scale") != currentNode.end())
        for(uint32_t i = 0; i < currentNode["scale"].size(); i++)
            scale[i] = (currentNode["scale"][i]);

    if(currentNode.find("matrix") != currentNode.end())
    {
        float matrixValues[16];
        for(uint32_t i = 0; i < currentNode["matrix"].size(); i++)
            matrixValues[i] = (currentNode["matrix"][i]);
        matrix = glm::make_mat4(matrixValues);
    }

    glm::mat4 positionMat = glm::mat4(1.0f);
    glm::mat4 rotationMat = glm::mat4(1.0f);
    glm::mat4 scaleMat = glm::mat4(1.0f);

    positionMat = glm::translate(positionMat, position);
    rotationMat = glm::mat4_cast(rotation);
    scaleMat = glm::scale(scaleMat, scale);

    glm::mat4 nextNodeMatrix = nodeMatrix * matrix * positionMat * rotationMat * scaleMat;

    if(currentNode.find("mesh") != currentNode.end())
    {
        m_positions.push_back(position);
        m_rotations.push_back(rotation);
        m_scales.push_back(scale);
        m_modelMatrices.push_back(matrix);

        loadMeshes(currentNode["mesh"]);
    }

    if(currentNode.find("children") != currentNode.end())
        for(uint32_t i = 0; i < currentNode["children"].size(); i++)
            treverseNode(currentNode["children"][i], nextNodeMatrix);
}


std::string glTFModel::readFile(const std::string& path)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    ASSERT(file, "Failed To Open The File: " + path)

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<unsigned char> glTFModel::getData()
{
    std::string modelText;
    std::string uri = m_JSON["buffers"][0]["uri"];

    std::string filePath = m_filePath;
    std::string fileDir = filePath.substr(0, filePath.find_last_of("/") + 1);
    modelText = readFile(fileDir + uri);

    std::vector<unsigned char> data(modelText.begin(), modelText.end());
    return data;
}

std::vector<float> glTFModel::getFloats(json accessor)
{
    uint32_t accessorBufferViewIndex = accessor.value("bufferView", 1);
    uint32_t accessorValuesCount = accessor["count"];
    uint32_t accessorByteOffset = accessor.value("byteOffset", 0);
    std::string accessorType = accessor["type"];

    json bufferView = m_JSON["bufferViews"][accessorBufferViewIndex];
    uint32_t byteOffset = bufferView["byteOffset"];

    uint32_t numOfFloats = 0;
    if(accessorType == "SCALAR")
        numOfFloats = 1;
    else if(accessorType == "VEC2")
        numOfFloats = 2;
    else if(accessorType == "VEC3")
        numOfFloats = 3;
    else if(accessorType == "VEC4")
        numOfFloats = 4;
    else
        ASSERT(true,
               "Unknown ValueType Spesified While Fetching Accessor Type in glTFModel: "
               + m_filePath);
    
    std::vector<float> floatVector;
    uint32_t dataBegin = byteOffset + accessorByteOffset;
    uint32_t dataLength = accessorValuesCount * sizeof(float) * numOfFloats;
    for(uint32_t i = dataBegin; i < dataBegin + dataLength;)
    {
        // we check the spesific index of the m_data char for the byte value in the bin file
        // and convert it into a value for us to access
        unsigned char bytes[] = {m_data[i++], m_data[i++], m_data[i++], m_data[i++]};
        float byteValue;
        std::memcpy(&byteValue, bytes, sizeof(float));

        floatVector.push_back(byteValue);
    }

    return floatVector;
}

std::vector<uint32_t> glTFModel::getIndices(json accessor)
{
    uint32_t accessorBufferViewIndex = accessor.value("bufferView", 0);
    uint32_t accessorValuesCount= accessor["count"];
    uint32_t accessorByteOffset = accessor.value("byteOffset", 0);
    uint32_t accessorComponentType = accessor["componentType"];

    json bufferView = m_JSON["bufferViews"][accessorBufferViewIndex];
    uint32_t byteOffset = bufferView["byteOffset"];

    std::vector<uint32_t> indicesVector;
    uint32_t dataBegin = byteOffset + accessorByteOffset;
    // we will check what type of a uint the value is and assign it accordingly
    switch(accessorComponentType)
    {
        case 5125: // uint32_t
            for(uint32_t i = dataBegin; i < dataBegin + accessorValuesCount * sizeof(uint32_t);)
            {
                unsigned char bytes[] = {m_data[i++], m_data[i++], m_data[i++], m_data[i++]};
                uint32_t byteValue;
                std::memcpy(&byteValue, bytes, sizeof(uint32_t));
                indicesVector.push_back((uint32_t)byteValue);
            }
        break;
        case 5123:
            for(uint32_t i = dataBegin; i < dataBegin + accessorValuesCount * sizeof(uint16_t);)
            {
                unsigned char bytes[] = {m_data[i++], m_data[i++]};
                uint16_t byteValue;
                std::memcpy(&byteValue, bytes, sizeof(uint16_t));
                indicesVector.push_back((uint32_t)byteValue);
            }
        break;
        case 5122:
            for(uint32_t i = dataBegin; i < dataBegin + accessorValuesCount * sizeof(int16_t);)
            {
                unsigned char bytes[] = {m_data[i++], m_data[i++]};
                int16_t byteValue;
                std::memcpy(&byteValue, bytes, sizeof(int16_t));
                indicesVector.push_back((uint32_t)byteValue);
            }
        break;
        default:
            ASSERT(true,
                   "Unknown ValueType While Fetching Accessor Component Type In glTFModel: "
                   + m_filePath);
    }

    return indicesVector;
}

std::vector<std::shared_ptr<Texture>> glTFModel::getTextures()
{
    std::vector<std::shared_ptr<Texture>> textures;

    std::string filePath = m_filePath;
    std::string fileDir = filePath.substr(0, filePath.find_last_of("/") + 1);

    for(uint32_t i = 0; i < m_JSON["images"].size(); i++)
    {
        std::string textureFile = m_JSON["images"][i]["uri"];
        
        bool skipTexture = false;
        for(uint32_t i = 0; i < m_loadedTextureNames.size(); i++)
        {
            if(m_loadedTextureNames[i] == textureFile)
            {
                textures.push_back(m_loadedTextures[i]);
                skipTexture = true;
                break;
            }
        }
        if(skipTexture) continue;

        if(textureFile.find("baseColor") != std::string::npos)
        {
            std::shared_ptr<Texture> diffuse = Texture::Create(
                fileDir + textureFile, TextureType::Diffuse);
            diffuse->Bind(m_loadedTextures.size());
            textures.push_back(diffuse);
            m_loadedTextures.push_back(diffuse);
            m_loadedTextureNames.push_back(textureFile);
        }
        else if(textureFile.find("metallicRoughness") != std::string::npos)
        {
            std::shared_ptr<Texture> roughness = Texture::Create(
                fileDir + textureFile, TextureType::Roughness);
            roughness->Bind(m_loadedTextures.size());
            textures.push_back(roughness);
            m_loadedTextures.push_back(roughness);
            m_loadedTextureNames.push_back(textureFile);
        }
    }

    return textures;
}

std::vector<Mesh> glTFModel::loadMeshes(uint32_t meshIndex)
{
    std::vector<Mesh> meshes;

    uint32_t positionIndex =
    m_JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["POSITION"];
    // uint32_t colorIndex =
    // m_JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["COLOR_0"];
    uint32_t textureCoordIndex =
    m_JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"];
    uint32_t normalIndex =
    m_JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["NORMAL"];
    uint32_t indicesIndex =
    m_JSON["meshes"][meshIndex]["primitives"][0]["indices"];

    std::vector<float> positions = getFloats(m_JSON["accessors"][positionIndex]);
    // std::vector<float> colors = getFloats(m_JSON["accessors"][colorIndex]);
    std::vector<float> texCoords = getFloats(m_JSON["accessors"][textureCoordIndex]);
    std::vector<float> normals = getFloats(m_JSON["accessors"][normalIndex]);

    std::vector<glm::vec3> positionVectors = groupVec<glm::vec3, 3>(positions);
    // std::vector<glm::vec3> colorVectors = groupVec<glm::vec3, 3>(colors);
    std::vector<glm::vec2> texCoordVectors = groupVec<glm::vec2, 2>(texCoords);
    std::vector<glm::vec3> normalVectors = groupVec<glm::vec3, 3>(normals);

    std::vector<ModelVertice> modelVertices =
    groupVertices(positionVectors, texCoordVectors, normalVectors);

    std::vector<uint32_t> indices = getIndices(m_JSON["accessors"][indicesIndex]);
    std::vector<std::shared_ptr<Texture>> textures = getTextures();

    meshes.push_back(Mesh(modelVertices, indices, textures));
    m_meshes.push_back(Mesh(modelVertices, indices, textures));

    return meshes;
}


template<typename T, uint32_t N>
std::vector<T> glTFModel::groupVec(const std::vector<float>& values)
{
    std::vector<T> vectors;
    for(uint32_t i = 0; i < values.size(); i += N)
    {
        T vector;
        for(uint32_t j = 0; j < N; j++)
            vector[j] = values[i + j];
        vectors.push_back(vector);
    }

    return vectors;
}

std::vector<ModelVertice> glTFModel::groupVertices(
    const std::vector<glm::vec3>& positions,
    const std::vector<glm::vec2>& texCoords,
    const std::vector<glm::vec3>& normals)
{
    std::vector<ModelVertice> vertices;
    for(uint32_t i = 0; i < positions.size(); i++)
    {
        vertices.push_back({
            positions[i],
            glm::vec3(1.0f, 1.0f, 1.0f),
            texCoords[i],
            normals[i]
        });
    }
    return vertices;
}