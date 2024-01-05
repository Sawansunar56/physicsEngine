#include "precompPch.h"
#include "Buffers.h"

#include <glad/glad.h>

IndexBuffers* IndexBuffers::Create(uint32_t* indices, uint32_t count) {
    return new IndexBuffers(indices, count);
}

VertexBuffers* VertexBuffers::Create(float* vertices, uint32_t size) {
    return new VertexBuffers(vertices, size);
}

VertexBuffers::VertexBuffers(float* vertices, uint32_t size) {
    glCreateBuffers(1, &m_RendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffers::~VertexBuffers() {
    glDeleteBuffers(1, &m_RendererId);
}

void VertexBuffers::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void VertexBuffers::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffers::IndexBuffers(uint32_t* indices, uint32_t count)
    : m_Count(count)
{
    glCreateBuffers(1, &m_RendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffers::~IndexBuffers() {
    glDeleteBuffers(1, &m_RendererId);
}

void IndexBuffers::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void IndexBuffers::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
