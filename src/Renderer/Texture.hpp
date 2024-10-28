#pragma once

#include <cstdint>
#include <memory>
#include <string>


enum class TextureType : short
{
    None        = 0,
    Diffuse     = 1,
    Roughness   = 2,
    Metallic    = 3,
    Normal      = 4
};

static std::string TextureTypeString(TextureType type)
{
    switch (type)
    {
        case TextureType::Diffuse:      return "Diffuse";
        case TextureType::Roughness:    return "Roughness";
        case TextureType::Metallic:     return "Metallic";
        case TextureType::Normal:       return "Normal";

        default: return "Unknown Texture Type";
    }
    return "Failed To Get TextureTypeString";
}


// @FIXME: this class is giving the GL_ERROR 1280 (INVALID ENUM) Error
class Texture
{
private:
    uint32_t m_textureID;
    std::string m_texFile;

    uint32_t m_width, m_height;
    int m_dataColorFormat, m_textureColorFormat;
    TextureType m_textureType;


private:
    void Init();

public:
    Texture() = default;
    Texture(const std::string& texPath);
    Texture(const std::string& texPath, TextureType type);
    ~Texture();

    uint32_t Get() { return m_textureID; }
    const std::string& GetFilePath() { return m_texFile; }

    uint32_t GetWidth() { return m_width; }
    uint32_t GetHeight() { return m_height; }

    TextureType GetTextureType() { return m_textureType; }
    void SetTextureType(TextureType type) { m_textureType = type; }

    void Bind(uint32_t slot = 0);
    void Unbind(uint32_t slot);

    static std::unique_ptr<Texture> Create(const std::string& texPath);
    static std::unique_ptr<Texture> Create(const std::string& texPath, TextureType type);
};