#pragma once
#include "glwrapper.h"
#include <string>

GLuint CompileShader(GLenum type, const std::string& source);

GLuint CompileProgram(const std::string& vsSource, const std::string& fsSource);

GLuint GenerateTexture();

void SetTexturePixels(GLuint textureId, GLsizei width, GLsizei height, GLubyte* pixels);

void DeleteTexture(GLuint textureId);

void CheckOpenGLError();