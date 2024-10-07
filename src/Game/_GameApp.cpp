#include "App/Application.hpp"

#include "Bagel/Game.hpp"


class GameApp : public Application
{
public:
    GameApp()
        : Application("Bagel")
    {
        AddComponent(new Game());
    }
};

Application* CreateApp()
{
    return new GameApp();
}