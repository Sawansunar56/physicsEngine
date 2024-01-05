#pragma once

#include "precompPch.h"
#include "events/Event.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct WindowProps {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "Physics Engine",
            unsigned int width = 1280,
            unsigned int height = 720)
        : Title(title), Width(width), Height(height) {}
};

class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(const WindowProps& props);
        static Window* Create(const WindowProps& props = WindowProps());
        void init(const WindowProps& props);
        void onUpdate();    
		inline void SetEventCallback(const EventCallbackFn& callback) { m_WindowData.EventCallback = callback; }

        inline void* GetNativeWindow() const { return m_Window; }

        inline unsigned int GetHeight() const { return m_WindowData.Height;}
        inline unsigned int GetWidth() const { return m_WindowData.Width;}
    
    private:
        GLFWwindow* m_Window;

        struct WindowsData {
            std::string Title;
            unsigned int Width, Height;
            
            EventCallbackFn EventCallback;
        };

        WindowsData m_WindowData;
};
