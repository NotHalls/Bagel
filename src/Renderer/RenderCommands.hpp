#pragma once

#include "ext/vector_float4.hpp"


class RenderCommand
{
public:
    static void ColorScreen(const glm::vec4& color);
    static void ResizeRenderer(int width, int height);
};