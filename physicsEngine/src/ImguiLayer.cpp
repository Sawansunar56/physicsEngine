#include "precompPch.h"
#include "events/MouseEvent.h"
#include "ImguiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "utils/log.h"

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
                                                        // / Platform Windows
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    Application &app = Application::Get();
    GLFWwindow *window =
        static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}
void ImGuiLayer::onDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End() {
    ImGuiIO &io = ImGui::GetIO();
    Application &app = Application::Get();
    io.DisplaySize =
        ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //     GLFWwindow *backup_current_context = glfwGetCurrentContext();
    //     ImGui::UpdatePlatformWindows();
    //     ImGui::RenderPlatformWindowsDefault();
    //     glfwMakeContextCurrent(backup_current_context);
    // }
}

void ImGuiLayer::onImGuiRender() {
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

bool onlyGoImGui(MouseButtonPressedEvent &e) {
    LOG_ERROR("From IMgui DEMO");
    return true;
}
void ImGuiLayer::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseButtonPressedEvent>(onlyGoImGui);
}
