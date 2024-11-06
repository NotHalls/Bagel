#pragma once


enum class EventType
{
    None = 0,
    WindowResize, WindowClose,
    KeyPress, KeyRelease,
    MouseClick, MouseRelease, MouseMove, MouseScroll
};


// We dont wanna type these in every single event type manually
// so we will create some Defines that will do it for us with a single line
#define SET_EVENT_TYPE(type) static EventType GetEventTypeStatic() { return EventType::type; }\
\
                            virtual EventType GetEventType() const override\
                            { return GetEventTypeStatic(); }\
\
                            virtual std::string GetEventTypeString() const override\
                            { return #type; }

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)
                            

class Event
{
friend class EventDispatcher;

public:
    bool m_handled = false;


public:
    virtual EventType GetEventType() const = 0;
    virtual std::string GetEventTypeString() const = 0;
    virtual std::string ToString() const = 0;
};


class EventDispatcher
{
private:
    Event& m_event;


public:
    EventDispatcher(Event& event)
        : m_event(event)
    {}

    template<typename T, typename F>
    bool Dispatch(const F& func)
    {
        if(m_event.GetEventType() == T::GetEventTypeStatic())
        {
            m_event.m_handled = func(static_cast<T&>(m_event));
            return true;
        }
        return false;
    }
};