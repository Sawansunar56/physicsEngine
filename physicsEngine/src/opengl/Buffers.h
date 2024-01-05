#pragma once

#include "precompPch.h"

class VertexBuffers {
    public:
        VertexBuffers(float* vertices, uint32_t size);
        ~VertexBuffers();
        void Bind() const;
        void Unbind() const;

        static VertexBuffers* Create(float* vertices, uint32_t size);
    private:
        uint32_t m_RendererId;
};

class IndexBuffers {
    public:
        IndexBuffers(uint32_t* indices, uint32_t count);
        ~IndexBuffers();
        void Bind() const;
        void Unbind() const;

        static IndexBuffers* Create(uint32_t* indices, uint32_t count);
        inline uint32_t GetCount() { return m_Count; }
    private:
        uint32_t m_RendererId;
        uint32_t m_Count;
};
