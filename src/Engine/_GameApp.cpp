#include "App/Application.hpp"

#include "_Bagel/Game.hpp"


class GameApp : public Application
{
public:
    GameApp()
        : Application("Bagel")
    {
        AddLayer(new Game());
    }
};

Application* CreateApp()
{
    return new GameApp();
}