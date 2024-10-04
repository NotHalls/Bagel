#pragma once

#include <cstdint>
#include <string>
#include <utility>


struct WindowInformation
{
    std::string WindowName = "Unnamed Window";

    uint32_t WindowWidth = 1280;
    uint32_t WindowHeight = 720;

    WindowInformation(  const std::string& windowName = "Unnamed Applicarion",
                        uint32_t windowWidth = 1280,
                        uint32_t windowHeight = 720)
        : WindowName(windowName),
          WindowWidth(windowWidth), WindowHeight(windowHeight)
    {}
};

class Window
{
public:
    virtual ~Window() {}

    virtual std::pair<uint32_t, uint32_t> getSize() const = 0;
    virtual void setSize(std::pair<uint32_t, uint32_t> size) = 0;

    virtual void* getWindow() = 0;

    virtual void Update() = 0;
    virtual void Close() = 0;

    static Window* CreateWindow(const WindowInformation& windowInfo = WindowInformation());
};