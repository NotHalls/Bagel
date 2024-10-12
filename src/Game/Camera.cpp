#include "Camera.hpp"


Camera::Camera(float FOV, float width, float height, float nearPlane, float farPlane)
    : m_position({0.0f, 0.0f, 0.0f}), m_rotation({0.0f, 0.0f, 0.0f}),
      m_view(glm::mat4(1.0f)), m_projection(glm::mat4(1.0f)),
      m_FOV(FOV), m_width(width), m_height(height),
      m_nearPlane(nearPlane), m_farPlane(farPlane)
{ RecalculateMatrices(); }


void Camera::RecalculateMatrices()
{
    m_view = glm::translate(glm::mat4(1.0f), m_position) *
             glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
             glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
             glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_projection = glm::perspective(m_FOV, m_width / m_height, m_nearPlane, m_farPlane);
}