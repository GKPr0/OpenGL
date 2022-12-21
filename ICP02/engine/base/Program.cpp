#include "Program.h"

#include <vector>

namespace Engine
{
    Program::Program(const std::string& vertFileName, const std::string& fragFileName)
    {
        Shader vertexShader = Shader::createVertexShader(vertFileName);
        Shader fragmentShader = Shader::createFragmentShader(fragFileName);
        createProgram(vertexShader, fragmentShader);
    }

    Program::Program(const Shader& vertexShader, const Shader& fragmentShader)
    {
        createProgram(vertexShader, fragmentShader);
    }

    void Program::createProgram(const Shader& vertexShader, const Shader& fragmentShader)
    {
        id = glCreateProgram();
        glAttachShader(id, vertexShader.getId());
        glAttachShader(id, fragmentShader.getId());
        glLinkProgram(id);

        int success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) 
        {
            std::string info = getProgramInfoLog(id);
            std::cerr << "Error creating program: " << info << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    std::string Program::getProgramInfoLog(const GLuint programId)
    {
        int infologLength = 0;
        std::string s;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infologLength);
        if (infologLength > 0) {
            std::vector<char> v(infologLength);
            glGetProgramInfoLog(programId, infologLength, NULL,
                v.data());
            s.assign(begin(v), end(v));
        }
        return s;
    }

    unsigned Program::getUniformId(const char* name) const
    {
        return glGetUniformLocation(id, name);
    }

    void Program::setInt(const char* name, int i) const
    {
        glUniform1i(getUniformId(name), i);
    }

    void Program::setFloat(const char* name, float f) const
    {
        glUniform1f(getUniformId(name), f);
    }

    void Program::setVec2(const char* name, const glm::vec2& vec) const
    {
        glUniform2fv(getUniformId(name), 1, glm::value_ptr(vec));
    }

    void Program::setVec3(const char* name, const glm::vec3& vec) const
    {
        glUniform3fv(getUniformId(name), 1, glm::value_ptr(vec));
    }

    void Program::setVec4(const char* name, const glm::vec4& vec) const
    {
        glUniform4fv(getUniformId(name), 1, glm::value_ptr(vec));
    }

    void Program::setMat2(const char* name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(getUniformId(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Program::setMat3(const char* name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(getUniformId(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Program::setMat4(const char* name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(getUniformId(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    Program::~Program()
    {
        clear();
    }

    void Program::clear()
    {
        //glDeleteProgram(id); //TODO some how i badyl manage programs
    }
}