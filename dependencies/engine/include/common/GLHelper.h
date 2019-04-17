#pragma once
#include "glwrapper.h"
#include "textures/Texture2D.h"
#include <string>

GLuint CompileShader(GLenum type, const std::string& source);

GLuint CompileProgram(const std::string& vsSource, const std::string& fsSource);

GLuint GenerateTexture();

void SetTexturePixels(Texture2D texture, GLubyte* pixels);

void DeleteTexture(GLuint textureId);

void CheckOpenGLError();