#pragma once

#include "Event.h"

class KeyEvent: public Event {
    public:
        KeyEvent(int keycode) : m_KeyCode(keycode) {}
        inline int GetKeyCode() const { return m_KeyCode; }
 
        EVENT_CLASS_TYPE(KeyPressed); 
    private:
        int m_KeyCode;
};
