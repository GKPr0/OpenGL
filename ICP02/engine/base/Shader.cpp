#include "Shader.h"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>


namespace Engine {

    Shader::Shader(const std::string& file, GLenum type): type(type)
    {
        std::string source = loadSource(file);
        const char* data = source.c_str();

        id = glCreateShader(type);
        glShaderSource(id, 1, &data, NULL);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) 
        {
            std::string info = getShaderInfoLog(id);
            std::cerr << "Error loading shader: " << info << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    std::string Engine::Shader::loadSource(const std::string& file)
    {
        std::ifstream fileStream;
        std::stringstream ss;

        fileStream.open(file);
        if (fileStream.is_open())
        {
            ss << fileStream.rdbuf();
        }
        else
        {
            std::cerr << "Error opening file: " << file << std::endl;
            exit(EXIT_FAILURE);
        }

        return std::move(ss.str());
    }

    std::string Shader::getShaderInfoLog(const GLuint id)
    {
        int infologLength = 0;
        std::string s;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infologLength);
        if (infologLength > 0) {
            std::vector<char> v(infologLength);
            glGetShaderInfoLog(id, infologLength, NULL,
                v.data());
            s.assign(begin(v), end(v));
        }
        return s;
    }

}

