#pragma once
#include "glwrapper.h"
#include <string>

namespace Engine {
    GLuint CompileShader(GLenum type, const std::string& source);

    GLuint CompileProgram(const std::string& vsSource, const std::string& fsSource);

    GLuint GenerateTexture();

    void SetTexturePixels(int textureIndex, int width, int height, bool hasAlpha, GLubyte* pixels);

    void DeleteTexture(int textureIndex);

    void CheckOpenGLError();
}
