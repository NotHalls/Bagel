#pragma once

#include "Tools/Tools.hpp"


enum HookCategory
{
    None = 0,
    AppEvent            = BIT(0),
    InputEvent          = BIT(1),
    KeyboardEvent       = BIT(2),
    MouseEvent          = BIT(3),
    MouseButtonEvent    = BIT(4)
};


class Hook
{

};