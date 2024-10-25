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

std::pair<float, float> Input::GetMousePosition()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getWindow());

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    return {xPos, yPos};
}


// SETTING INNPUT MODES //
void Input::SetCursorMode(int mode)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getWindow());

    glfwSetInputMode(window, GLFW_CURSOR, mode);
}



// CALLBACK FUNCTIONS //
void Input::OnMouseMove(const std::function<void(float, float)>& function)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getWindow());

    static std::function<void(float, float)> mouseFunction = function;

    glfwSetCursorPosCallback(window, static_cast<GLFWcursorposfun>(
        [](GLFWwindow* window, double xPos, double yPos)
        {
            mouseFunction((float)xPos, (float)yPos);
        }
    ));
}