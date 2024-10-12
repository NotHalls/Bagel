#include <utility>

#include <GLFW/glfw3.h>

#include "App/Application.hpp"

#include "Input/Input.hpp"


bool Input::IsKeyClicked(int keycode)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getWindow());

    int state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseClicked(int keycode)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getWindow());

    int state = glfwGetMouseButton(window, keycode);
    return state == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getWindow());

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    return {xPos, yPos};
}