#pragma once

#include <cstdint>
#include <memory>


class VertexArray
{
private:
    uint32_t m_VAO;


public:
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();

    static std::unique_ptr<VertexArray> Create();
};