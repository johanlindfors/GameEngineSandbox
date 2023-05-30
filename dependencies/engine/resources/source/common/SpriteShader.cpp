#include "resources/SpriteShader.hpp"
#include "utilities/MathHelper.hpp"

using namespace Engine;

SpriteShader *SpriteShader::loadShader(
        const std::string &vertexSource,
        const std::string &fragmentSource) {
    SpriteShader *shader = nullptr;

    GLuint program = ShaderBase::loadShader(
        vertexSource, 
        fragmentSource);
    if (program > 0) {
        shader = new SpriteShader(
                program,
                0,
                1);
    }
    return shader;
}

void SpriteShader::setMvpMatrix(const std::string &name, float *mvpMatrix) const {
    glUniformMatrix4fv(GlGetUniformLocation(mProgram, name.c_str()), 1, false, mvpMatrix);
}
