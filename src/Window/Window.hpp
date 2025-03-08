#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <utility>

#include "Events/Events.hpp"

struct WindowInformation
{
  std::string WindowName = "Unnamed Window";

  uint32_t WindowWidth = 800;
  uint32_t WindowHeight = 600;

  WindowInformation(const std::string &windowName = "Unnamed Applicarion",
                    uint32_t windowWidth = 800, uint32_t windowHeight = 600)
      : WindowName(windowName), WindowWidth(windowWidth),
        WindowHeight(windowHeight)
  {
  }
};

class Window
{
public:
  using FunctionCallback = std::function<void(Event &)>;

public:
  virtual ~Window() {}

  virtual std::pair<uint32_t, uint32_t> getSize() const = 0;

  virtual void *getWindow() = 0;

  virtual void SetCallbackFunction(const FunctionCallback &callback) = 0;

  virtual void Update() = 0;

  virtual float GetElapsedWindowTime() = 0;

  static Window *CreateWindow(
      const WindowInformation &windowInfo = WindowInformation());
};