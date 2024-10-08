#pragma once

#include <cstdint>
#include <memory>


class VertexBuffer
{
private:
    uint32_t m_VBO;


public:
    VertexBuffer() = default;
    VertexBuffer(const float* buffer, uint32_t size);
    ~VertexBuffer();

    void Bind();
    void Unbind();

    static std::shared_ptr<VertexBuffer> Create(const float* buffer, uint32_t size);
};


class IndexBuffer
{
private:
    uint32_t m_IBO;


public:
    IndexBuffer() = default;
    IndexBuffer(uint32_t* buffer, uint32_t count);
    ~IndexBuffer();

    void Bind();
    void Unbind();

    static std::shared_ptr<IndexBuffer> Create(uint32_t* buffer, uint32_t count);
};