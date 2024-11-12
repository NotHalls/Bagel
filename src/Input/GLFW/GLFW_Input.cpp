#include <utility>

#include <GLFW/glfw3.h>

#include "App/Application.hpp"

#include "Input/Input.hpp"


// TAKING INPUT //
bool Input::IsKeyClicked(int keycode)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getWindow());

    int state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseClicked(int button)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getWindow());

    int state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}


// SETTING INNPUT MODES //
void Input::SetCursorMode(int mode)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getWindow());

    glfwSetInputMode(window, GLFW_CURSOR, mode);
}