#include <stdexcept>
#include <string>

#include "Application.hpp"
#include "Component.hpp"


Application* Application::m_app = nullptr;

Application::Application(const std::string& appName)
{
    if(m_app)
        throw std::runtime_error("An Instance Of Application Class Already Exists");
    m_app = this;

    m_window = std::unique_ptr<Window>(Window::CreateWindow(WindowInformation(appName)));
}

void Application::Run()
{
    for(Component* component : m_components)
    {
        component->Start();
    }

    float lastTime = 0.0f;

    while(!CloseApplication)
    {
        double time = m_window->GetElapsedWindowTime();
        double dt = time - lastTime;
        lastTime = time;

        m_window->Update();
        
        // we will call update from the master Component class
        //which will call all of its child component
        for(Component* component : m_components)
        {
            component->Update(dt);
        }
    }
}

void Application::Close()
{
    m_window->Close();
    CloseApplication = true;
}


void Application::AddComponent(Component* component)
{ m_components.AddComponent(component); }
void Application::RemoveComponent(Component* component)
{ m_components.RemoveComponent(component); }