#include <iostream>
#include <stdexcept>
#include <string>
#include <ranges>

#include "Application.hpp"
#include "Layer.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/RenderCommands.hpp"

#include "Events/WindowEvents.hpp"



Application* Application::m_app = nullptr;

Application::Application(const std::string& appName)
{
    if(m_app)
        throw std::runtime_error("An Instance Of Application Class Already Exists");
    m_app = this;

    m_window = std::unique_ptr<Window>(Window::CreateWindow(WindowInformation(appName)));
    m_window->SetCallbackFunction(BIND_EVENT(Application::ProcessEvents));

    RenderCommand::Init(m_window->getSize().first, m_window->getSize().second);
    Renderer::Init({
        "assets/shaders/2DShader.vertex.glsl",
        "assets/shaders/2DShader.fragment.glsl"
    });
}

void Application::ProcessEvents(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(Application::Resize));
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::Close));

    for(Layer* layer : std::ranges::reverse_view(m_layerLists))
    {
        layer->ProcessEvent(event);
    }
}

void Application::Run()
{
    for(Layer* layer : m_layerLists)
    {
        layer->Start();
    }

    float lastTime = 0.0f;

    while(!CloseApplication)
    {
        double time = m_window->GetElapsedWindowTime();
        double dt = time - lastTime;
        lastTime = time;

        m_window->Update();

        // we will call update from the master Layer class
        //which will call all of its child layer
        for(Layer* layer : m_layerLists)
        {
            layer->Update(dt);
        }
    }
}

bool Application::Resize(WindowResizeEvent& windowResizeEvent)
{
    RenderCommand::ResizeRenderer(windowResizeEvent.GetWidth(), windowResizeEvent.GetHeight());

    return false;
}

bool Application::Close(WindowCloseEvent& windowCloseEvent)
{
    CloseApplication = true;

    return false;
}


void Application::AddLayer(Layer* layer)
{ m_layerLists.AddLayer(layer); }
void Application::RemoveLayer(Layer* layer)
{ m_layerLists.RemoveLayer(layer); }
