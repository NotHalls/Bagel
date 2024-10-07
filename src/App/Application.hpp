#pragma once

#include <memory>
#include <string>

#include "Window/Window.hpp"
#include "Object.hpp"
#include "ObjectList.hpp"


class Application
{
private:
    static Application* m_app;
    bool CloseApplication = false;

    std::unique_ptr<Window> m_window;

    ObjectList m_objects;


public:
    Application(const std::string& appName);

    static Application& Get() { return *m_app; }

    void Run();
    void Close();

    void AddObject(Object* object);
    void RemoveObject(Object* object);
};

Application* CreateApp();