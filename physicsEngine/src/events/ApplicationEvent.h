#include "Event.h"

class WindowCloseEvent : public Event {
    public: 
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose);
};
