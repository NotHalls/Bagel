#pragma once

#include <cstdint>
#include <memory>
#include <string>


// @FIXME: this class is giving the GL_ERROR 1280 (INVALID ENUM) Error
class Texture
{
private:
    uint32_t m_textureID;
    std::string m_texFile;

    uint32_t m_width, m_height;
    int m_dataColorFormat, m_textureColorFormat;

private:

public:
    Texture() = default;
    Texture(const std::string& texPath);
    ~Texture();

    uint32_t Get() { return m_textureID; }
    const std::string& GetFilePath() { return m_texFile; }

    uint32_t GetWidth() { return m_width; }
    uint32_t GetHeight() { return m_height; }

    void Bind(uint32_t slot = 0);
    void Unbind(uint32_t slot);

    static std::shared_ptr<Texture> Create(const std::string& texPath);
};