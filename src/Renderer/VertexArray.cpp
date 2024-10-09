#include <memory>

#include <glad/glad.h>

#include "VertexArray.hpp"


std::unique_ptr<VertexArray> VertexArray::Create()
{ return std::make_unique<VertexArray>(); }


VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
}
VertexArray::~VertexArray()
{ glDeleteVertexArrays(1, &m_VAO); }

void VertexArray::Bind()
{ glBindVertexArray(m_VAO); }
void VertexArray::Unbind()
{ glBindVertexArray(0); }