#pragma once

#include "Renderer/Camera.hpp"

#include "Events/Events.hpp"
#include "Events/InputEvents.hpp"
#include "Events/WindowEvents.hpp"

class CameraController
{
private:
  Camera m_camera;

  float m_mouseSensitivity;
  float m_speed;

  float m_yaw;
  float m_pitch;
  float m_lastX, m_lastY;

  bool m_firstMouse;

public:
  CameraController(float FOV, float width, float height, float nearPlane = 0.1f,
                   float farPlane = 100.0f, float sensi = 0.1f,
                   float speed = 5.0f);

  void SetSpeed(float speed) { m_speed = speed; }
  float GetSpeed() const { return m_speed; }

  void SetMouseSensitivity(float sensi) { m_mouseSensitivity = sensi; }
  float GetMouseSensitivity() const { return m_mouseSensitivity; }

  const Camera &GetCamera() const { return m_camera; }

  void OnUpdate(float dt);
  void OnEvent(Event &event);

  bool OnMouseMove(MouseMoveEvent &mousemoveEvent);
  bool OnResize(WindowResizeEvent &windowResizeEvent);
};