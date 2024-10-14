#include "Camera.hpp"


Camera::Camera(float FOV, float width, float height, float nearPlane, float farPlane)
    : m_position({0.0f, 0.0f, 0.0f}), m_target({0.0f, 0.0f, -1.0f}),
      m_view(glm::mat4(1.0f)), m_projection(glm::mat4(1.0f)),
      m_FOV(FOV), m_width(width), m_height(height),
      m_nearPlane(nearPlane), m_farPlane(farPlane)
{
    RecalculateProjection();
    RecalculateView();
}


void Camera::RecalculateView()
{
    m_view = glm::lookAt(m_position, m_position + m_target, glm::vec3(0.0f, 1.0f, 0.0f));
    RecalculateMatrices();
}

void Camera::RecalculateProjection()
{
    m_projection = glm::perspective(m_FOV, m_width / m_height, m_nearPlane, m_farPlane);
    RecalculateMatrices();
}

void Camera::RecalculateMatrices()
{ m_ViewAndProjection = m_projection * m_view; }