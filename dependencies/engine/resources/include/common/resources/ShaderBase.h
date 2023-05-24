#pragma once
#include <string>
#include "utilities/GLHelper.h"

namespace Engine {
class Model;

class ShaderBase {
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
     * @return a valid Shader on success, otherwise null.
     */
    static GLuint loadShader(
            const std::string &vertexSource,
            const std::string &fragmentSource);

    inline ~ShaderBase() {
        if (mProgram) {
            glDeleteProgram(mProgram);
            mProgram = 0;
        }
    }

    /*!
     * Prepares the shader for use, call this before executing any draw commands
     */
    virtual void activate() const;

    /*!
     * Cleans up the shader after use, call this after executing any draw commands
     */
    virtual void deactivate() const;

    GLuint GetProgramID() { return mProgram; }

    /*!
     * Renders a single model
     * @param model a model to render
     */
    virtual void drawModel(const Model &model) const;

private:
    /*!
     * Helper function to load a shader of a given type
     * @param shaderType The OpenGL shader type. Should either be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
     * @param shaderSource The full source of the shader
     * @return the id of the shader, as returned by glCreateShader, or 0 in the case of an error
     */
    static GLuint loadShader(GLenum shaderType, const std::string &shaderSource);

    /*!
     * Constructs a new instance of a shader. Use @a loadShader
     * @param program the GL program id of the shader
     */
protected:
    constexpr ShaderBase(
            GLuint program, GLint position, GLint uv)
            : mProgram(program)
            , mPosition(position)
            , mUV(uv)
            {}

    GLuint mProgram;
    GLint mPosition;
    GLint mUV;
};
}