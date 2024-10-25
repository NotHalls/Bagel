#pragma once

#include <cstdint>
#include <memory>

#include "Renderer/Buffer.hpp"


class VertexArray
{
private:
    uint32_t m_VAO;


public:
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);

    static std::unique_ptr<VertexArray> Create();
};