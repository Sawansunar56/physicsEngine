#include "precompPch.h"
#include "Engine.h"
#include "utils/log.h"

#include "imgui.h"
#include "events/MouseEvent.h"

Engine::Engine() : Layer("Engine Layer") {
    m_VertexArray.reset(VertexArray::Create());

    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.33f, 0.2f, 0.8, 1.0f,
                        0.0f,  0.5f,  0.0f, 0.33f, 0.2f, 0.8, 1.0f,
                        0.5f,  -0.5f, 0.0f, 0.33f, 0.2f, 0.8, 1.0f};

    m_VertexArray->Bind();
    m_VertexBuffer.reset(VertexBuffers::Create(vertices, sizeof(vertices)));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                          (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    uint32_t indices[] = {0, 1, 2};

    m_IndexBuffer.reset(
        IndexBuffers::Create(indices, sizeof(indices) / sizeof(uint32_t)));

    std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

            void main() {
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

    std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

			in vec4 v_Color;
            uniform vec4 u_Color;

            void main() {
                color = u_Color;
            }
        )";

    m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
}

void Engine::onUpdate(Timestep ts) {
    m_Shader->Bind();
    m_Shader->UploadUniformFloat4("u_Color", m_Colors);
    m_VertexArray->Bind();

    glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT,
                   nullptr);
}

void Engine::onImGuiRender() {
    ImGui::Begin("SeTTINGS");
    ImGui::Text("What is the fucking hell?");
    ImGui::ColorEdit4("change color", m_Colors);
    ImGui::End();
}

bool onlyGoEngine(MouseButtonPressedEvent &e) {
    LOG_ERROR("FUCKING ONLY ON ENGINE SECTION");
    return true;
}
void Engine::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseButtonPressedEvent>(onlyGoEngine);
}

