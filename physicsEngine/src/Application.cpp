#include "precompPch.h"
#include "Application.h"
#include <imgui.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils/log.h"
#include "utils/Timestep.h"
#include "windows/Window.h"
#include "events/Event.h"
#include "Engine.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application *Application::s_Instance = nullptr;

bool Application::onWindowClose(WindowCloseEvent &e) {
    m_Running = false;
    LOG_CRITICAL("Hate the shit");
    return true;
}

bool Application::keyPress(KeyEvent &e) {
    LOG_INFO("HIT KEY: {0}", e.GetKeyCode());
    return true;
}

bool Application::onWindowResize(WindowResizeEvent &e) {
    LOG_INFO("RESIZE: {0}, {1}", e.GetWidth(), e.GetHeight());
    return true;
}

bool Application::onMouseClick(MouseButtonPressedEvent &e) {
    LOG_INFO("MOUSE CLICK: {0}", e.GetMouseButton());
    return true;
}

bool Application::onMouseRelease(MouseButtonReleasedEvent &e) {
    LOG_INFO("MOUSE Release: {0}", e.GetMouseButton());
    return true;
}

void Application::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
    dispatcher.Dispatch<KeyEvent>(BIND_EVENT_FN(keyPress));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(onWindowResize));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(
        BIND_EVENT_FN(onMouseRelease));
    dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(onMouseClick));
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->onEvent(e);
        if (e.handled)
            break;
    }
}

Application::Application() {
    s_Instance = this;
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));

    m_imguiLayer = new ImGuiLayer();
    PushLayer(new Engine());
    PushLayer(m_imguiLayer);
}

Application::~Application() {}

void Application::Run() {

    while (m_Running) {
        glClear(GL_COLOR_BUFFER_BIT);
        float time = (float)glfwGetTime();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        for (Layer *layer : m_LayerStack) {
            layer->onUpdate(timestep);
        }

        m_imguiLayer->Begin();
        for (Layer *layer : m_LayerStack) {
            layer->onImGuiRender();
        }
        m_imguiLayer->End();

        m_Window->onUpdate();
    }
}

void Application::PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer *layer) { m_LayerStack.PushOverLay(layer); }
