#include <iostream>
#include <ostream>
#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "App/Application.hpp"
#include "glfwWinfow.hpp"

#include "Events/InputEvents.hpp"
#include "Events/WindowEvents.hpp"

void GlfwErrorCallback(int error, const char *description)
{
  std::cout << "Error Was Called By GLFW: " << error
            << " With The Description: " << description << std::endl;
}

Window *Window::CreateWindow(const WindowInformation &windowInfo)
{
  return new GlfwWindow(windowInfo);
}

GlfwWindow::GlfwWindow(const WindowInformation &windowInfo)
{
  initializeGLFW(windowInfo);
}
GlfwWindow::~GlfwWindow() { CloseWindow(); }

void GlfwWindow::initializeGLFW(const WindowInformation &windowInfo)
{
  m_glfwWindowInfo.WindowName = windowInfo.WindowName;
  m_glfwWindowInfo.WindowWidth = windowInfo.WindowWidth;
  m_glfwWindowInfo.WindowHeight = windowInfo.WindowHeight;

  if(!glfwInit())
    glfwSetErrorCallback(GlfwErrorCallback);

  // the latest version of opengl when i commited this is 4.6
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwSetErrorCallback(GlfwErrorCallback);
  m_mainWindow = glfwCreateWindow(
      m_glfwWindowInfo.WindowWidth, m_glfwWindowInfo.WindowHeight,
      m_glfwWindowInfo.WindowName.c_str(), nullptr, nullptr);
  if(m_mainWindow == nullptr)
  {
    std::cout << "Failed To Create GLFW Window" << std::endl;
    glfwSetErrorCallback(GlfwErrorCallback);
    CloseWindow();
  }
  glfwMakeContextCurrent(m_mainWindow);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Failed To Load OpenGL From GLAD LOADER");

  glfwSetWindowUserPointer(m_mainWindow, &m_glfwWindowInfo);

  // WINDOW SPESIFIC EVENTS
  glfwSetWindowSizeCallback(
      m_mainWindow, [](GLFWwindow *window, int width, int height) {
        glfwWindowInformation &windowInfo =
            *(glfwWindowInformation *)glfwGetWindowUserPointer(window);
        windowInfo.WindowWidth = width;
        windowInfo.WindowHeight = height;

        WindowResizeEvent windowResizeEvent(width, height);
        windowInfo.CallbackFunc(windowResizeEvent);
      });

  glfwSetWindowCloseCallback(m_mainWindow, [](GLFWwindow *window) {
    glfwWindowInformation &windowInfo =
        *(glfwWindowInformation *)glfwGetWindowUserPointer(window);

    WindowCloseEvent windowCloseEvent;
    windowInfo.CallbackFunc(windowCloseEvent);
  });

  glfwSetCursorPosCallback(
      m_mainWindow, [](GLFWwindow *window, double xPos, double yPos) {
        glfwWindowInformation &windowInfo =
            *(glfwWindowInformation *)glfwGetWindowUserPointer(window);

        MouseMoveEvent mouseMoveEvent((float)xPos, (float)yPos);
        windowInfo.CallbackFunc(mouseMoveEvent);
      });
}

void GlfwWindow::Update()
{
  glfwSwapBuffers(m_mainWindow);
  glfwPollEvents();
}
void GlfwWindow::CloseWindow()
{
  glfwDestroyWindow(m_mainWindow);
  glfwTerminate();
}