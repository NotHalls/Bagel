#include "App/Application.hpp"


extern Application* CreateApp();

int main()
{
    Application* App = CreateApp();

    App->Run();

    // @FIXME: im getting glfw errors while closing the app
    // i know that im getting those because glfw is probably not being closed when i close my app
    // and im trying to access glfw functions. like Input or GetGlfwTime
}