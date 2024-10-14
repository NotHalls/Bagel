#pragma once

#include <utility>

#include "BagelMath.hpp"


class Input
{
public:
    // TAKING INPUT //
    static bool IsKeyClicked(int keycode);
    static bool IsMouseClicked(int button);

    static std::pair<float, float> GetMousePosition();


    // SETING INPUT MODES //
    static void SetCursorMode(int mode);


    // CALLBACK FUNCTIONS //
    static void OnMouseMove(const std::function<void(float, float)>& function);
};