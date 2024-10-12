#pragma once

#include <utility>


class Input
{
public:
    static bool IsKeyClicked(int keycode);
    static bool IsMouseClicked(int keycode);

    static std::pair<float, float> GetMousePosition();
};