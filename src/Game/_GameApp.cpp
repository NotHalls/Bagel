#include "App/Application.hpp"

#include "Game.hpp"


class GameApp : public Application
{
public:
    GameApp()
        : Application("Bagel")
    {
        AddObject(new Game());
    }
};

Application* CreateApp()
{
    return new GameApp();
}