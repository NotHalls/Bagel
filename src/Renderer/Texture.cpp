#include <memory>

#include "stb_image.hpp"
#include <glad/glad.h>

#include "Texture.hpp"
#include "Tools/Debug.hpp"

std::unique_ptr<Texture> Texture::Create(const std::string &texPath)
{
  return std::make_unique<Texture>(texPath);
}
std::unique_ptr<Texture> Texture::Create(const std::string &texPath,
                                         TextureType type)
{
  return std::make_unique<Texture>(texPath, type);
}
std::unique_ptr<Texture> Texture::Create(int width, int height)
{
  return std::make_unique<Texture>(width, height);
}

Texture::Texture(int width, int height) : m_width(width), m_height(height)
{
  InitWithDefaults();
}
Texture::Texture(const std::string &texPath)
    : m_texFile(texPath), m_textureID(0), m_width(0), m_height(0)
{
  Init();
}
Texture::Texture(const std::string &texPath, TextureType type)
    : m_texFile(texPath), m_textureID(0), m_width(0), m_height(0),
      m_textureType(type)
{
  Init();
}
Texture::~Texture() { glDeleteTextures(1, &m_textureID); }

void Texture::Init()
{
  int width, height, channels;
  stbi_uc *textureData =
      stbi_load(m_texFile.c_str(), &width, &height, &channels, 0);

  ASSERT(textureData, "Failed To Load Image");

  m_width = width;
  m_height = height;

  int internalCF, externalCF;

  if(channels == 4)
  {
    internalCF = GL_RGBA8;
    externalCF = GL_RGBA;
  }
  else if(channels == 3)
  {
    internalCF = GL_RGB8;
    externalCF = GL_RGB;
  }

  m_dataColorFormat = internalCF;
  m_textureColorFormat = externalCF;

  glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
  glTextureStorage2D(m_textureID, 1, m_dataColorFormat, m_width, m_height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height,
                      m_textureColorFormat, GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(textureData);

  glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::InitWithDefaults()
{
  // @TODO: We Have To Make A Default Texture
  // like how we made a Default Model thing
  m_dataColorFormat = GL_RGBA8;
  m_textureColorFormat = GL_RGBA;

  glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
  glTextureStorage2D(m_textureID, 1, m_dataColorFormat, m_width, m_height);

  glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::SetData(void *data, uint32_t size)
{
  // remember, when you give the RGBA data, it is reversed (ABGR) not (RGBA)
  // so 0xAABBGGRR not 0xRRGGBBAA

  uint32_t bytesPerPixel = m_textureColorFormat == GL_RGBA ? 4 : 3;
  ASSERT(size == m_width * m_height * bytesPerPixel,
         "Invalid Size Of Texture Data.\
        \n The Size Should Be The Same As The Whole Texture")
  glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height,
                      m_textureColorFormat, GL_UNSIGNED_BYTE, data);
}

void Texture::Bind(uint32_t slot) { glBindTextureUnit(slot, m_textureID); }
void Texture::Unbind(uint32_t slot) { glBindTextureUnit(slot, 0); }