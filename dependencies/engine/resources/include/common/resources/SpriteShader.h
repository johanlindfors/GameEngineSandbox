#pragma once
#include <string>
#include "ShaderBase.h"

namespace Engine
{
    class SpriteShader : public ShaderBase
    {
        public:
        static SpriteShader *loadShader(
                const std::string &vertexSource,
                const std::string &fragmentSource);

        void setMvpMatrix(const std::string &name, float *mvpMatrix) const;

    private:
        constexpr SpriteShader(
                GLuint program,
                GLint position,
                GLint uv)
                : ShaderBase(program, position, uv)
                {}
    };
}