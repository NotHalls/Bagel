#include <glad/glad.h>

#include "RenderCommands.hpp"
#include "ext/vector_float4.hpp"


void RenderCommand::ColorScreen(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderCommand::ResizeRenderer(int width, int height)
{
    glViewport(0, 0, width, height);
}