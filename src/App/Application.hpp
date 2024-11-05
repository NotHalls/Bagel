#pragma once

#include <memory>
#include <string>

#include "Window/Window.hpp"
#include "Component.hpp"
#include "ComponentList.hpp"

#include "Events/Events.hpp"
#include "Events/WindowEvents.hpp"


class Application
{
private:
    static Application* m_app;
    bool CloseApplication = false;

    std::unique_ptr<Window> m_window;

    ComponentList m_components;


public:
    Application(const std::string& appName);

    static Application& Get() { return *m_app; }
    Window& GetWindow() { return *m_window; }

    void Run();
    void ProcessEvents(Event& event);

    bool Resize(WindowResizeEvent& windowResizeEvent);
    bool Close(WindowCloseEvent& windowCloseEvent);

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
};

Application* CreateApp();