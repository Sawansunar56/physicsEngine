#include "Event.h"

class WindowCloseEvent : public Event {
    public: 
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose);
};

class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(int height, int width) :
            m_width(width), m_height(height) {}

        inline unsigned int GetWidth() const { return m_width; }
        inline unsigned int GetHeight() const { return m_height; }

        EVENT_CLASS_TYPE(WindowResize);
    private:
        unsigned int m_height, m_width;
};
