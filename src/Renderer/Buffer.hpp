#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

#include "BufferLayout.hpp"

class VertexBuffer
{
private:
  uint32_t m_VBO;
  BufferLayout m_bufferLayout;

public:
  VertexBuffer() {}
  VertexBuffer(const float *buffer, uint32_t size);
  ~VertexBuffer();

  void Bind();
  void Unbind();

  void SetBufferLayout(const BufferLayout &layout) { m_bufferLayout = layout; }
  const BufferLayout &GetBufferLayout() const { return m_bufferLayout; }

  static std::shared_ptr<VertexBuffer> Create(const float *buffer,
                                              uint32_t size);
};

class IndexBuffer
{
private:
  uint32_t m_IBO;

public:
  IndexBuffer() = default;
  IndexBuffer(uint32_t *buffer, uint32_t count);
  ~IndexBuffer();

  void Bind();
  void Unbind();

  static std::shared_ptr<IndexBuffer> Create(uint32_t *buffer, uint32_t count);
};