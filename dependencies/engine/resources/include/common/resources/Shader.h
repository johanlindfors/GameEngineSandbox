#pragma once
#include "utilities/GLHelper.h"
#include "glm/glm.hpp"

namespace Engine {
    class Shader {
    public:
        unsigned int ID;
        Shader() = default;
        ~Shader();
        void Use();
        void CreateShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
        void SetInteger(const std::string& name, int value);
        void SetVector2f(const std::string& name, float x, float y);
        void SetVector3f(const std::string&name, float x, float y, float z);
        void SetVector4f(const std::string& name, float x, float y, float z, float w);
        void SetMatrix4(const std::string& name, glm::mat4 &matrix);
    private:
        std::string mName;
    };
}
