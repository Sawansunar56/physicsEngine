#include "precompPch.h"
#include "Application.h"
#include "utils/Log.h"

int main() {
    Log::Init();
    /* Loop until the user closes the window */
    Application app;

    app.Run();

    glfwTerminate();
    return 0;
}
