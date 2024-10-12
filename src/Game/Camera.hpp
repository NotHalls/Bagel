#pragma once

#include "BagelMath.hpp"


class Camera
{
private:
    glm::mat4 m_view;
    glm::mat4 m_projection;

    glm::vec3 m_position;
    glm::vec3 m_rotation;

    float m_FOV;
    float m_width, m_height;
    float m_nearPlane, m_farPlane;


private:
    void RecalculateMatrices();

public:
    Camera(float FOV, float width, float height, float nearPlane = 0.1f, float farPlane = 100.0f);

    const glm::mat4& GetViewMatrix() const { return m_view; }
    const glm::mat4& GetProjectionMatrix() const { return m_projection; }

    float GetFOV() const { return m_FOV; }
    void SetFOV(float fov) { m_FOV = fov; RecalculateMatrices(); }

    float GetWidth() const { return m_width; }
    float GetHeight() const { return m_height; }
    void SetWidth(float width) { m_width = width; RecalculateMatrices(); }
    void SetHeight(float height) { m_height = height; RecalculateMatrices(); }

    const glm::vec3& GetPosition() const { return m_position; }
    const glm::vec3& GetRotation() const { return m_rotation; }
    void SetPosition(const glm::vec3& position) { m_position = position; RecalculateMatrices(); }
    void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; RecalculateMatrices(); }
};