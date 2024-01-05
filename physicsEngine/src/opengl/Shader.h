#pragma once
#include "precompPch.h"

class Shader {
    public:
        Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
        ~Shader() ;
        void Bind() const ;
        void Unbind() const;

        static Shader* Create(const std::string &vertexSrc, const std::string &fragmentSrc);
    private:
        uint32_t m_RendererId;
};
