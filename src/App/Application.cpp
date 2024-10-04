#include <stdexcept>
#include <string>

#include <GLFW/glfw3.h>

#include "Application.hpp"
#include "Object.hpp"


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
    for(Object* obj : m_objects)
    {
        obj->Start();
    }

    float lastTime = 0.0f;

    while(!CloseApplication)
    {
        float time = glfwGetTime();
        float dt = time - lastTime;
        lastTime = time;

        m_window->Update();
        
        // we will call update from the master Object class
        //which will call all of its child objects
        for(Object* obj : m_objects)
        {
            obj->Update(dt);
        }
    }
}

void Application::Close()
{
    m_window->Close();
    CloseApplication = true;
}


void Application::AddObject(Object* object)
{ m_objects.AddObject(object); }
void Application::RemoveObject(Object* object)
{ m_objects.RemoveObject(object); }