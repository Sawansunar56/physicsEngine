#pragma once

#include "Layer.h"
#include "opengl/VertexArray.h"
#include "opengl/Buffers.h"
#include "opengl/Shader.h"

#include <glad/glad.h>

class Engine : public Layer {
  public:
    Engine();
    ~Engine(){};

    virtual void onUpdate(Timestep ts) override;
    static Engine *Create() { return new Engine(); }

  private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexBuffers> m_VertexBuffer;
    std::shared_ptr<IndexBuffers> m_IndexBuffer;
};
