#pragma once

#include "Events.hpp"

#include <sstream>

#include "BagelMath.hpp"


class MouseMoveEvent : public Event
{
private:
    float m_mouseX, m_mouseY;

public:
    MouseMoveEvent(float x, float y)
        : m_mouseX(x), m_mouseY(y)
    {}

    SET_EVENT_TYPE(MouseMove)

    const glm::vec2 GetMouseAxis() const { return {m_mouseX, m_mouseY}; }

    virtual std::string ToString() const override
    {
        std::stringstream msg;
        msg << "MouseX: " << m_mouseX << ", MouseY: " << m_mouseY;
        return msg.str();
    }
};