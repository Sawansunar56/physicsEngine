#pragma once

#include "precompPch.h"
#include "events/Event.h"
#include "events/KeyEvent.h"
#include "events/ApplicationEvent.h"
#include "events/MouseEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "windows/Window.h"
#include "ImguiLayer.h"

class Application {
  public:
    Application();
    virtual ~Application();

    void Run();

    void onEvent(Event &e);
    void PushLayer(Layer *layer);
    void PushOverlay(Layer *layer);

    inline Window &GetWindow() { return *m_Window; }
    inline static Application& Get() { return *s_Instance; }

  private:
    bool keyPress(KeyEvent &e);
    bool onWindowClose(WindowCloseEvent &e);
    bool onWindowResize(WindowResizeEvent &e);
    bool onMouseClick(MouseButtonPressedEvent &e);
    bool onMouseRelease(MouseButtonReleasedEvent &e);

  private:
    LayerStack m_LayerStack;
    ImGuiLayer* m_imguiLayer;
    std::unique_ptr<Window> m_Window;
    static Application* s_Instance;
    float m_LastFrameTime;

    bool m_Running = true;
};
