#pragma once

#include "BagelMath.hpp"


class Camera
{
private:
    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::mat4 m_ViewAndProjection;

    glm::vec3 m_position;
    glm::vec3 m_lookAt;

    float m_FOV;
    float m_width, m_height;
    float m_nearPlane, m_farPlane;


private:
    void RecalculateView();
    void RecalculateProjection();
    void RecalculateMatrices();

public:
    Camera(float FOV, float width, float height, float nearPlane = 0.1f, float farPlane = 100.0f);

    const glm::mat4& GetViewMatrix() const { return m_view; }
    const glm::mat4& GetProjectionMatrix() const { return m_projection; }
    const glm::mat4& GetViewAndProjectionMatrix() const { return m_ViewAndProjection; }

    float GetFOV() const { return m_FOV; }
    void SetFOV(float fov) { m_FOV = fov; RecalculateProjection(); }

    float GetWidth() const { return m_width; }
    float GetHeight() const { return m_height; }
    void SetWidth(float width) { m_width = width; RecalculateProjection(); }
    void SetHeight(float height) { m_height = height; RecalculateProjection(); }
    void SetSize(float width, float height) { m_width = width; m_height = height;
        RecalculateProjection(); }

    const glm::vec3& GetPosition() const { return m_position; }
    void SetPosition(const glm::vec3& position) { m_position = position; RecalculateView(); }

    const glm::vec3& GetLookingTarget() const { return m_lookAt; }
    void SetLookingTarget(const glm::vec3& lookTarget) { m_lookAt = lookTarget; RecalculateView(); }
};