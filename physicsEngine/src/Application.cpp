#include "precompPch.h"
#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utils/log.h>
#include "windows/Window.h"
#include "events/Event.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

bool Application::onWindowClose(WindowCloseEvent &e) {
    m_Running = false;
    LOG_CRITICAL("Hate the shit");
    return true;
}

bool Application::keyPress(KeyEvent &e) {
    LOG_INFO("HIT KEY: {0}", e.GetKeyCode());
    return true;
}

Application::Application() {
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));
}

Application::~Application() {}

void Application::Run() {
    while(m_Running) {
        for (Layer* layer: m_LayerStack) {
            layer->onUpdate();
        }
        m_Window->onUpdate();
    }
}

void Application::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
    dispatcher.Dispatch<KeyEvent>(BIND_EVENT_FN(keyPress));
}

void Application::PushLayer(Layer *layer) {
    m_LayerStack.PushLayer(layer);
    layer->onAttach();
}

void Application::PushOverlay(Layer *layer) {
    m_LayerStack.PushOverLay(layer);
    layer->onDetach();
}

