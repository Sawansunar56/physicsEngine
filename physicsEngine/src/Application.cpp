#include "precompPch.h"
#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utils/log.h>
#include "windows/Window.h"
#include "events/Event.h"
#include "events/KeyEvent.h"
#include "events/ApplicationEvent.h"

static bool mRunningState = true;
bool onWindowClose(WindowCloseEvent& e) {
    mRunningState = false;
    LOG_CRITICAL("Hate the shit");
    return true;
}

bool keyPress(KeyEvent& e) {
    LOG_INFO("HIT KEY: {0}", e.GetKeyCode());
    return true;
}

void OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(onWindowClose);
    dispatcher.Dispatch<KeyEvent>(keyPress);
}

int main()
{
    Log::Init();    
    std::unique_ptr<Window> m_Window;
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(OnEvent);

	/* Loop until the user closes the window */
	while (mRunningState)
	{
	    m_Window->onUpdate();
	}

	glfwTerminate();
	return 0;
}
