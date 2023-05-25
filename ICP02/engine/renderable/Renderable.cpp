#include "Renderable.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
    
    GLuint Renderable::getVao() const
    {
        return vao;
    }

    glm::mat4 Renderable::getModelMatrix() const
    {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, mPosition);
        matrix = glm::scale(matrix, mScale);
        matrix = matrix * mRotation;
        return matrix;
    }

    void Renderable::translate(const glm::vec3& translate)
    {
        mPosition += translate;
    }

    void Renderable::scale(const glm::vec3& vec)
    {
        mScale = vec;
    }

    void Renderable::rotate(const float& angle, const glm::vec3& vec)
    {
        mRotation = glm::rotate(mRotation, glm::radians(angle), vec);
    }

    void Renderable::rotateX(const float& angle)
    {
        rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    void Renderable::rotateY(const float& angle)
    {
        rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void Renderable::rotateZ(const float& angle)
    {
        rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
    }

}

