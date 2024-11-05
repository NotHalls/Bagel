#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include <GLFW/glfw3.h>

#include "Window.hpp"


class GlfwWindow : public Window
{
private:
    GLFWwindow* m_mainWindow = nullptr;

    // window size
    virtual std::pair<uint32_t, uint32_t> getSize() const override
    { return {m_glfwWindowInfo.WindowWidth, m_glfwWindowInfo.WindowHeight}; }

    virtual void* getWindow() override { return m_mainWindow; }
    virtual float GetElapsedWindowTime() override { return glfwGetTime(); }

    virtual void SetCallbackFunction(const FunctionCallback& callback) override
    { m_glfwWindowInfo.CallbackFunc = callback; }

    virtual void Update() override;

    void CloseWindow();


private:
    struct glfwWindowInformation
    {
        std::string WindowName = "Unnamed GLFW Window";
        uint32_t WindowWidth, WindowHeight;

        FunctionCallback CallbackFunc;
    };
    glfwWindowInformation m_glfwWindowInfo;


public:
    GlfwWindow(const WindowInformation& windowInfo);
    ~GlfwWindow();

    void initializeGLFW(const WindowInformation& windowInfo);
}; 