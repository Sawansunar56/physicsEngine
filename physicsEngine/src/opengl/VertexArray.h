#pragma once

#include "precompPch.h"

class VertexArray {
    public:
        VertexArray();
        ~VertexArray();
        void Bind() const;
        void Unbind() const;

        static VertexArray* Create();

    private:
        uint32_t m_RendererId;
};
