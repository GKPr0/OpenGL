#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
    class Program
    {
        unsigned id = 0;

        void createProgram(const Shader& vertexShader, const Shader& fragmentShader);

        std::string getProgramInfoLog(const GLuint programId);
        unsigned getUniformId(const char* name) const;

        void clear();

    public:
        Program(){};
        Program(const Shader& vertex, const Shader& fragment);
        Program(const std::string& vertFileName, const std::string& fragFileName);
        ~Program();

        void use() const { glUseProgram(id); }

        void setInt(const char* name, int i) const;
        void setFloat(const char* name, float f) const;
        void setVec2(const char* name, const glm::vec2& vec) const;
        void setVec3(const char* name, const glm::vec3& vec) const;
        void setVec4(const char* name, const glm::vec4& vec) const;
        void setMat2(const char* name, const glm::mat2& mat) const;
        void setMat3(const char* name, const glm::mat3& mat) const;
        void setMat4(const char* name, const glm::mat4& mat) const;

        unsigned getId() const { return id; }
    };
}