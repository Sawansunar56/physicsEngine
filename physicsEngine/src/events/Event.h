#pragma once

#include "precompPch.h"

enum class EventType {
    WindowClose,
    KeyPressed
};

#ifdef __clang__
#define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; } 
#else
#define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::##type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; } 
#endif

class Event {
    friend class EventDispatcher;
   public:
       bool handled = false;
       virtual EventType GetEventType() const = 0;
       virtual const char* GetName() const = 0;
};


class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) : m_Event(event) {}

        template<typename T>
        bool Dispatch(EventFn<T> func) {
            if(m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.handled = func(*(T*)&m_Event);
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;

};
