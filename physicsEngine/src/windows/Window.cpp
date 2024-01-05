#include "precompPch.h"
#include "Window.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "events/ApplicationEvent.h"
#include "utils/log.h"

static bool s_GLFWInitialized = false;

Window::Window(const WindowProps& props)
{
    init(props);
}

Window* Window::Create(const WindowProps& props)
{
    return new Window(props);
}

void Window::init(const WindowProps& props)
{
    m_WindowData.Title = props.Title;
    m_WindowData.Height = props.Height;
    m_WindowData.Width = props.Width;

    if (!s_GLFWInitialized) {
        int success = glfwInit();
        LOG_ASSERT(success, "could not initialize GLFW");

        s_GLFWInitialized = true;
    }

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialize GLAD");
    }

    /* Make the window's context current */
    glfwSetWindowUserPointer(m_Window, &m_WindowData);

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(
        m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
        }
    });


    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

        WindowResizeEvent event(height, width);
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
        if (action == GLFW_PRESS) {
            KeyEvent event(key);
            data.EventCallback(event);
        }
    });
}

void Window::onUpdate()
{
    /* Render here */

    glfwPollEvents();
    /* Swap front and back buffers */
    glfwSwapBuffers(m_Window);

    /* Poll for and process events */
}
