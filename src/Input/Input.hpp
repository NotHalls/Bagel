#pragma once

#include <utility>

#include "BagelMath.hpp"


class Input
{
public:
    // TAKING INPUT //
    static bool IsKeyClicked(int keycode);
    static bool IsMouseClicked(int button);


    // SETING INPUT MODES //
    static void SetCursorMode(int mode);
};