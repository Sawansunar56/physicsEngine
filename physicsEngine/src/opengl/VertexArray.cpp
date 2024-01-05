#include "precompPch.h"
#include "VertexArray.h"

#include <glad/glad.h>

VertexArray* VertexArray::Create() {
    return new VertexArray();
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererId);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererId);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_RendererId);
}

void VertexArray::Unbind() const {
 glBindVertexArray(0);
}

