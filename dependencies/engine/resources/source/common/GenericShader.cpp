#include "resources/GenericShader.h"
#include "resources/Model.h"
#include "utilities/MathHelper.h"

using namespace Engine;

GenericShader *GenericShader::loadShader(
        const std::string &vertexSource,
        const std::string &fragmentSource,
        const std::string &positionAttributeName,
        const std::string &uvAttributeName,
        const std::string &projectionMatrixUniformName) {
    GenericShader *shader = nullptr;

    GLint positionAttribute, uvAttribute;
    GLuint program = ShaderBase::loadShader(
        vertexSource, 
        fragmentSource, 
        positionAttributeName, 
        uvAttributeName,
        positionAttribute,
        uvAttribute);
    if (program > 0) {
        GLint projectionMatrixUniform = glGetUniformLocation(
                program,
                projectionMatrixUniformName.c_str());

        // Only create a new shader if all the attributes are found.
        if (projectionMatrixUniform != -1 &&
            positionAttribute != -1 &&
            uvAttribute != -1) {

            shader = new GenericShader(
                    program,
                    positionAttribute,
                    uvAttribute,
                    projectionMatrixUniform);
        } else {
            glDeleteProgram(program);
        }
    }
    return shader;
}

void GenericShader::setMvpMatrix(float *mvpMatrix) const {
    glUniformMatrix4fv(mMvpMatrix, 1, false, mvpMatrix);
}
