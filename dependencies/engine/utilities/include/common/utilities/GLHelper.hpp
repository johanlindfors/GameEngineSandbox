#pragma once
#include "utilities/glwrapper.hpp"
#include <string>

namespace Engine
{
    GLuint compileShader(GLenum type, const std::string &source);

    GLuint compileProgram(const std::string &vsSource, const std::string &fsSource);

    GLuint generateTexture();

    void setTexturePixels(int textureIndex, int width, int height, bool hasAlpha, GLubyte *pixels);

    void deleteTexture(int textureIndex);

    void checkOpenGLError();

    // Wrapping gl*

    GLint GlCreateProgram();
    void GlUseProgram(GLuint program);
    void GlDeleteProgram(GLuint program);
    void GlLinkProgram(GLuint program);
    void GlGetProgramiv(GLuint program, GLenum pname, GLint *params);
    void GlGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

    void GlGenVertexArrays(GLsizei n, GLuint *arrays);
    void GlBindVertexArray(GLuint array);
    void GlEnableVertexAttribArray(GLuint index);
    void GlDrawArrays(GLenum mode, GLint first, GLsizei count);
    void GlDisableVertexAttribArray(GLuint index);

    void GlDeleteBuffers(GLsizei n, const GLuint *buffers);
    void GlBindBuffer(GLenum target, GLuint buffer);
    void GlGenBuffers(GLsizei n, GLuint *buffers);
    void GlBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

    void GlActiveTexture(GLenum texture);
    void GlBindTexture(GLenum target, GLuint texture);
    void GlTexParameteri(GLenum target, GLenum pname, GLint param);
    void GlGenTextures(GLsizei n, GLuint *textures);
    void GlPixelStorei(GLenum pname, GLint param);
    void GlTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
    void GlDeleteTextures(GLsizei n, const GLuint *textures);

    void GlViewport(GLint x, GLint y, GLsizei width, GLsizei height);
    void GlClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void GlClear(GLbitfield mask);
    void GlEnable(GLenum cap);
    void GlBlendFunc(GLenum sfactor, GLenum dfactor);
    void GlVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    void GlDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices);
    GLint GlGetAttribLocation(GLuint program, const GLchar *name);
    GLint GlGetUniformLocation(GLuint program, const GLchar *name);
    void GlUniform1i(GLint location, GLint v0);
    void GlUniform2f(GLint location, GLfloat v0, GLfloat v1);
    void GlUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    void GlUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    void GlUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    void GlUniform4fv(GLint location, GLsizei count, const GLfloat *value);
    void GlUniform2fv(GLint location, GLsizei count, const GLfloat *value);

    GLuint GlCreateShader(GLenum type);
    void GlDeleteShader(GLuint shader);
    void GlShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);
    void GlCompileShader(GLuint shader);
    void GlGetShaderiv(GLuint shader, GLenum pname, GLint *params);
    void GlGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    void GlAttachShader(GLuint program, GLuint shader);

    GLenum GlGetError();
    void GlDisable(GLenum cap);
}
