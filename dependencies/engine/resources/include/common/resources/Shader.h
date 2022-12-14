#pragma once
#include "utilities/GLHelper.h"

namespace Engine {
    class Shader {
    public:
        void Use();
        void CreateShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
        void SetInteger(const std::string& name, int value);
        void SetVector2f(const std::string& name, float x, float y);
        void SetVector4f(const std::string& name, float x, float y, float z, float w);
        void SetMatrix4(const std::string& name, glm::mat4 &matrix);
    private:
        unsigned int mProgramId;
        std::string mName;
    };
}
