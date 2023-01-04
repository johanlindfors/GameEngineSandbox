#pragma once
#include "utilities/GLHelper.h"
#include "glm/glm.hpp"

namespace Engine {
    class Shader {
    public:
        unsigned int ID;
        Shader() = default;
        ~Shader();
        void use();
        void createShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
        void setInteger(const std::string& name, int value);
        void setVector2f(const std::string& name, float x, float y);
        void setVector3f(const std::string&name, float x, float y, float z);
        void setVector4f(const std::string& name, float x, float y, float z, float w);
        void setMatrix4(const std::string& name, glm::mat4 &matrix);
    private:
        std::string mName;
    };
}
