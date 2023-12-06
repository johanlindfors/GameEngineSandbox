#pragma once
#include "utilities/GLHelper.hpp"
#include "glm/glm.hpp"
#include "utilities/MathHelper.hpp"

namespace Engine
{
    class Shader
    {
    public:
        unsigned int ID;
        Shader() = default;
        ~Shader();
        void use();
        void createShader(const std::string &name, const std::string &vertexShader, const std::string &fragmentShader);
        void setInteger(const std::string &name, int value);
        void setVector2f(const std::string &name, float x, float y);
        void setVector3f(const std::string &name, float x, float y, float z);
        void setVector4f(const std::string &name, float x, float y, float z, float w);
        void setVector4fv(const std::string &name, Utilities::Vector4 vec);
        void setMatrix4(const std::string &name, const glm::mat4 &matrix);
        int getAttribLocation(const std::string &name) const;

    private:
        std::string mName;
    };
}
