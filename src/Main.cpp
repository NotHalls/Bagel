#include "App/Application.hpp"


extern Application* CreateApp();

int main()
{
    Application* App = CreateApp();

    App->Run();
}