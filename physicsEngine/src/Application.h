#pragma once

#include "events/Event.h"
#include "events/KeyEvent.h"
#include "events/ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "windows/Window.h"

class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void onEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        bool keyPress(KeyEvent &e);
        bool onWindowClose(WindowCloseEvent &e);
    private:
        LayerStack m_LayerStack;
        std::unique_ptr<Window> m_Window;

        bool m_Running = true;
};
