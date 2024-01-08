#pragma once
#include "Event.h"

class MouseButtonEvent : public Event {
    public:
        inline int GetMouseButton() const { return m_Button; }

    protected:
        MouseButtonEvent(int button) : m_Button(button) {}

        int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonReleased)
};
