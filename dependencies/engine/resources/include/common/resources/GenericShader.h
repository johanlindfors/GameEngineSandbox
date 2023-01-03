#pragma once
#include <string>
#include "ShaderBase.h"

namespace Engine
{
    class GenericShader : public ShaderBase
    {
        public:
    /*!
     * Loads a shader given the full sourcecode and names for necessary attributes and uniforms to
     * link to. Returns a valid shader on success or null on failure. Shader resources are
     * automatically cleaned up on destruction.
     *
     * @param vertexSource The full source code for your vertex program
     * @param fragmentSource The full source code of your fragment program
     * @param positionAttributeName The name of the position attribute in your vertex program
     * @param uvAttributeName The name of the uv coordinate attribute in your vertex program
     * @param projectionMatrixUniformName The name of your model/view/projection matrix uniform
     * @return a valid Shader on success, otherwise null.
     */
    static GenericShader *loadShader(
            const std::string &vertexSource,
            const std::string &fragmentSource,
            const std::string &positionAttributeName,
            const std::string &uvAttributeName,
            const std::string &mvpMatrixUniformName);

    /*!
     * Sets the model/view/projection matrix in the shader.
     * @param mvpMatrix sixteen floats, column major, defining an OpenGL model, view, projection matrix.
     */
    void setMvpMatrix(float *mvpMatrix) const;

private:
    /*!
     * Constructs a new instance of a shader. Use @a loadShader
     * @param program the GL program id of the shader
     * @param position the attribute location of the position
     * @param uv the attribute location of the uv coordinates
     * @param projectionMatrix the uniform location of the projection matrix
     */
    constexpr GenericShader(
            GLuint program,
            GLint position,
            GLint uv,
            GLint mvpMatrix)
            : ShaderBase(program, position, uv),
              mMvpMatrix(mvpMatrix) {}

    GLint mMvpMatrix;
    };
}