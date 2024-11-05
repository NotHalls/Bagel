#pragma once

#include "Events.hpp"

#include <sstream>


class WindowResizeEvent : public Event
{
private:
    uint32_t m_windowWidth, m_windowHeight;


public:
    WindowResizeEvent(uint32_t width, uint32_t height)
        : m_windowWidth(width), m_windowHeight(height)
    {}

    SET_EVENT_TYPE(WindowResize)

    uint32_t GetWidth() const { return m_windowWidth; }
    uint32_t GetHeight() const { return m_windowHeight; }

    virtual std::string ToString() const override
    {
        std::stringstream msg;
        msg << "Width: " << m_windowWidth << ", Height: " << m_windowHeight;
        return msg.str();
    }
};


class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() {}

    SET_EVENT_TYPE(WindowClose)

    virtual std::string ToString() const override
    { return "Window Closed!"; }
};