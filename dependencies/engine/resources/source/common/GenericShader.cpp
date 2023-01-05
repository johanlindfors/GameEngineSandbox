#include "resources/GenericShader.h"
#include "resources/Model.h"
#include "utilities/MathHelper.h"

using namespace Engine;

GenericShader *GenericShader::loadShader(
        const std::string &vertexSource,
        const std::string &fragmentSource,
        const std::string &positionAttributeName,
        const std::string &uvAttributeName,
        const std::string &mvpMatrixUniformName) {
    GenericShader *shader = nullptr;

    GLuint program = ShaderBase::loadShader(
        vertexSource, 
        fragmentSource);
    if (program > 0) {
        GLint positionAttribute = GlGetAttribLocation(
                program,
                positionAttributeName.c_str());
        printf("Position: %d\n", positionAttribute);
        GLint uvAttribute = GlGetAttribLocation(
                program,
                uvAttributeName.c_str());
        printf("UV: %d\n", uvAttribute);
        GLint mvpMatrixUniform = glGetUniformLocation(
                program,
                mvpMatrixUniformName.c_str());
        printf("MVP: %d\n", mvpMatrixUniform);
        // Only create a new shader if all the attributes are found.
        if (mvpMatrixUniform != -1 &&
            positionAttribute != -1 &&
            uvAttribute != -1) {
            shader = new GenericShader(
                    program,
                    positionAttribute,
                    uvAttribute,
                    mvpMatrixUniform);
        } else {
            glDeleteProgram(program);
        }
    }
    return shader;
}

GenericShader *GenericShader::loadShader(
        const std::string &vertexSource,
        const std::string &fragmentSource,
        GLint positionAttribute,
        GLint uvAttribute,
        GLint mvpMatrixUniform) {
    GenericShader *shader = nullptr;
    GLuint program = ShaderBase::loadShader(
        vertexSource, 
        fragmentSource);
    if (program > 0) {
        // Only create a new shader if all the attributes are found.
        if (mvpMatrixUniform != -1 &&
            positionAttribute != -1 &&
            uvAttribute != -1) {
            shader = new GenericShader(
                    program,
                    positionAttribute,
                    uvAttribute,
                    mvpMatrixUniform);
        } else {
            glDeleteProgram(program);
        }
    }
    return shader;
}

void GenericShader::setMvpMatrix(float *mvpMatrix) const {
    glUniformMatrix4fv(mMvpMatrix, 1, false, mvpMatrix);
}
