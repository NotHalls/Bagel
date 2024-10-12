#include <glad/glad.h>

#include "_Renderer.hpp"
#include "ext/vector_float4.hpp"


void Renderer::ColorScreen(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}