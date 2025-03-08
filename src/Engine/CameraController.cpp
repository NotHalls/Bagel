#include <iostream>

#include "CameraController.hpp"

#include "BagelInput.hpp"

CameraController::CameraController(float FOV, float width, float height,
                                   float nearPlane, float farPlane, float sensi,
                                   float speed)
    : m_camera(FOV, width, height, nearPlane, farPlane),
      m_mouseSensitivity(sensi), m_speed(speed)
{
  m_yaw = -90.0f;
  m_pitch = 0.0f;
  m_lastX = (float)800 / 2;
  m_lastY = (float)600 / 2;
  m_firstMouse = true;
}

void CameraController::OnUpdate(float dt)
{
  glm::vec3 camPosition = m_camera.GetPosition();
  if(Input::IsKeyClicked(BG_KEY_W))
    camPosition += m_camera.GetLookingTarget() * m_speed * dt;
  if(Input::IsKeyClicked(BG_KEY_S))
    camPosition -= m_camera.GetLookingTarget() * m_speed * dt;
  if(Input::IsKeyClicked(BG_KEY_A))
    camPosition -= glm::normalize(glm::cross(m_camera.GetLookingTarget(),
                                             {0.0f, 1.0f, 0.0f})) *
                   m_speed * dt;
  if(Input::IsKeyClicked(BG_KEY_D))
    camPosition += glm::normalize(glm::cross(m_camera.GetLookingTarget(),
                                             {0.0f, 1.0f, 0.0f})) *
                   m_speed * dt;
  m_camera.SetPosition(camPosition);

  if(Input::IsKeyClicked(BG_KEY_F))
    Input::SetCursorMode(BG_CURSOR_MODE_DISABLED);
}

void CameraController::OnEvent(Event &event)
{
  EventDispatcher dispatcher(event);

  dispatcher.Dispatch<MouseMoveEvent>(
      BIND_EVENT(CameraController::OnMouseMove));
  dispatcher.Dispatch<WindowResizeEvent>(
      BIND_EVENT(CameraController::OnResize));
}

bool CameraController::OnMouseMove(MouseMoveEvent &mouseMoveEvent)
{
  if(m_firstMouse)
  {
    m_lastX = mouseMoveEvent.GetMouseAxis().x;
    m_lastY = mouseMoveEvent.GetMouseAxis().y;

    m_firstMouse = false;
  }

  float xOffset = mouseMoveEvent.GetMouseAxis().x - m_lastX;
  float yOffset = m_lastY - mouseMoveEvent.GetMouseAxis().y;
  m_lastX = mouseMoveEvent.GetMouseAxis().x;
  m_lastY = mouseMoveEvent.GetMouseAxis().y;

  xOffset *= m_mouseSensitivity;
  yOffset *= m_mouseSensitivity;

  m_yaw += xOffset;
  m_pitch += yOffset;

  if(m_pitch > 89.0f)
    m_pitch = 89.0f;
  else if(m_pitch < -89.0f)
    m_pitch = -89.0f;

  glm::vec3 dir = glm::vec3(0.0f);
  dir.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  dir.y = sin(glm::radians(m_pitch));
  dir.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_camera.SetLookingTarget(dir);

  return false;
}

bool CameraController::OnResize(WindowResizeEvent &windowResizeEvent)
{
  m_camera.SetSize(windowResizeEvent.GetWidth(), windowResizeEvent.GetHeight());

  return false;
}