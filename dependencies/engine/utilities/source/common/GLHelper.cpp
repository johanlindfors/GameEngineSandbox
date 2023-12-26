#include "utilities/GLHelper.hpp"
#include "utilities/Logger.hpp"
#include <vector>
// #define DEBUG 1
#ifdef DEBUG
#define TRACE(x) debuglog << x;
#else
#define TRACE(x)       \
	do                 \
	{                  \
		if (0)         \
			debuglog << x; \
	} while (0)
#endif /* DEBUG */

using namespace std;

namespace Engine
{

	GLuint compileShader(GLenum type, const string &source)
	{
		TRACE("[GLHelper::CompileShader] Compiling shader\n");

		const auto shader = GlCreateShader(type);

		TRACE("[GLHelper::CompileShader] Shader created\n");
		const char *sourceArray[1] = {source.c_str()};
		GlShaderSource(shader, 1, sourceArray, nullptr);
		GlCompileShader(shader);
		TRACE("[GLHelper::CompileShader] Shader compiled\n");

		checkOpenGLError();

		GLint compileResult;
		GlGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

		if (compileResult == 0)
		{
			GLint infoLogLength;
			GlGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			GlGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			printf("Compilation error in shader: '%s'\n", strInfoLog);
			delete[] strInfoLog;
		}

		return shader;
	}

	GLuint compileProgram(const string &vsSource, const string &fsSource)
	{
		TRACE("[GLHelper::CompileProgram] Creating program\n");
		checkOpenGLError();
		const auto program = GlCreateProgram();
		if (program == 0)
		{
			TRACE("[GLHelper::CompileProgram] Failed to create program -- should exit!\n");
			checkOpenGLError();
		}
		else
		{
			TRACE("[GLHelper::CompileProgram] Program created\n");
		}

		const auto vs = compileShader(GL_VERTEX_SHADER, vsSource);
		TRACE("[GLHelper::CompileProgram] Vertex shader compiled\n");
		const auto fs = compileShader(GL_FRAGMENT_SHADER, fsSource);
		TRACE("[GLHelper::CompileProgram] Fragment shader compiled\n");

		if (vs == 0 || fs == 0)
		{
			GlDeleteShader(fs);
			GlDeleteShader(vs);
			GlDeleteProgram(program);
			return 0;
		}

		GlAttachShader(program, vs);
		GlDeleteShader(vs);

		GlAttachShader(program, fs);
		GlDeleteShader(fs);

		GlLinkProgram(program);
		TRACE("[GLHelper::CompileProgram] Program linked\n");

		GLint linkStatus;
		GlGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		checkOpenGLError();

		if (linkStatus == 0)
		{
			GLint infoLogLength;
			GlGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			vector<GLchar> infoLog(infoLogLength);
			GlGetProgramInfoLog(program, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());

			auto errorMessage = string(infoLog.begin(), infoLog.end());
			printf("Program link failed: %s\n", errorMessage.c_str());
		}

		return program;
	}

	// Needs to be called on UI thread
	GLuint generateTexture()
	{
		// Texture object handle
		GLuint textureId = 0;
		// Generate a texture object
		GlGenTextures(1, &textureId);
		printf("[GLHelper::GenerateTexture] TextureId: '%d'\n", textureId);
		checkOpenGLError();
		return textureId;
	}

	// Need to be called on UI thread
	void setTexturePixels(int textureIndex, int width, int height, bool hasAlpha, GLubyte *pixels)
	{
		TRACE("[GLHelper::SetTexturePixels]\n");
		// Bind the texture object
		GlBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(textureIndex));
		GlPixelStorei(GL_PACK_ALIGNMENT, 1);
		GlPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		checkOpenGLError();
		GlTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, pixels);
		checkOpenGLError();
		// Set the filtering mode
		GlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		GlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void deleteTexture(int textureIndex)
	{
		auto glTextureIndex = static_cast<GLuint>(textureIndex);
		GlDeleteTextures(1, &glTextureIndex);
	}

	void checkOpenGLError()
	{
		const auto err = GlGetError();
		if (err != GL_NO_ERROR)
		{
			debuglog << "OpenGL error " << err;
			exit(1);
		}
	}

	void GlDeleteBuffers(GLsizei n, const GLuint *buffers)
	{
		TRACE("[GLHelper::GlDeleteBuffers]\n");
		glDeleteBuffers(n, buffers);
	}

	void GlDeleteProgram(GLuint program)
	{
		TRACE("[GLHelper::GlDeleteProgram]\n");
		glDeleteProgram(program);
	}

	void GlViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		TRACE("[GLHelper::GlViewport]\n");
		glViewport(x, y, width, height);
	}

	void GlClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		TRACE("[GLHelper::GlClearColor]\n");
		glClearColor(red, green, blue, alpha);
	}

	void GlClear(GLbitfield mask)
	{
		TRACE("[GLHelper::GlClear]\n");
		glClear(mask);
	}

	void GlDisable(GLenum cap)
	{
		TRACE("[GLHelper::GlDisable]\n");
		glDisable(cap);
	}

	void GlActiveTexture(GLenum texture)
	{
		TRACE("[GLHelper::GlActiveTexture]\n");
		glActiveTexture(texture);
	}

	void GlBindTexture(GLenum target, GLuint texture)
	{
		TRACE("[GLHelper::GlBindTexture]\n");
		glBindTexture(target, texture);
	}

	void GlEnable(GLenum cap)
	{
		TRACE("[GLHelper::GlEnable]\n");
		glEnable(cap);
	}

	void GlBlendFunc(GLenum sfactor, GLenum dfactor)
	{
		TRACE("[GLHelper::GlBlendFunc]\n");
		glBlendFunc(sfactor, dfactor);
	}

	void GlTexParameteri(GLenum target, GLenum pname, GLint param)
	{
		TRACE("[GLHelper::GlTexParameteri]\n");
		glTexParameteri(target, pname, param);
	}

	void GlBindBuffer(GLenum target, GLuint buffer)
	{
		TRACE("[GLHelper::GlBindBuffer]\n");
		glBindBuffer(target, buffer);
	}

	void GlEnableVertexAttribArray(GLuint index)
	{
		TRACE("[GLHelper::GlEnableVertexAttribArray]\n");
		glEnableVertexAttribArray(index);
	}

	void GlVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
	{
		TRACE("[GLHelper::GlVertexAttribPointer]\n");
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	void GlDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
	{
		TRACE("[GLHelper::GlDrawElements]\n");
		glDrawElements(mode, count, type, indices);
	}

	GLint GlGetAttribLocation(GLuint program, const GLchar *name)
	{
		TRACE("[GLHelper::GlGetAttribLocation]\n");
		return glGetAttribLocation(program, name);
	}

	void GlGenBuffers(GLsizei n, GLuint *buffers)
	{
		TRACE("[GLHelper::GlGenBuffers]\n");
		glGenBuffers(n, buffers);
	}

	void GlBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
	{
		TRACE("[GLHelper::GlBufferData]\n");
		glBufferData(target, size, data, usage);
	}

	GLint GlGetUniformLocation(GLuint program, const GLchar *name)
	{
		TRACE("[GLHelper::GlGetUniformLocation]\n");
		return glGetUniformLocation(program, name);
	}

	void GlUniform1i(GLint location, GLint v0)
	{
		TRACE("[GLHelper::GlUniform1i]\n");
		glUniform1i(location, v0);
	}

	void GlUniform2f(GLint location, GLfloat v0, GLfloat v1)
	{
		TRACE("[GLHelper::GlUniform2f]\n");
		glUniform2f(location, v0, v1);
	}

	void GlUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
		TRACE("[GLHelper::GlUniform3f]\n");
		glUniform3f(location, v0, v1, v2);
	}

	void GlUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
		TRACE("[GLHelper::GlUniform4f]\n");
		glUniform4f(location, v0, v1, v2, v3);
	}

	void GlUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		TRACE("[GLHelper::GlUniformMatrix4fv]\n");
		glUniformMatrix4fv(location, count, transpose, value);
	}

	void GlUseProgram(GLuint program)
	{
		TRACE("[GLHelper::GlUseProgram]\n");
		glUseProgram(program);
	}

	void GlDeleteShader(GLuint shader)
	{
		TRACE("[GLHelper::GlDeleteShader]\n");
		glDeleteShader(shader);
	}

	void GlShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length)
	{
		TRACE("[GLHelper::GlShaderSource]\n");
		glShaderSource(shader, count, string, length);
	}

	GLint GlCreateProgram()
	{
		TRACE("[GLHelper::GlCreateProgram]\n");
		return glCreateProgram();
	}

	GLuint GlCreateShader(GLenum type)
	{
		TRACE("[GLHelper::GlCreateShader]\n");
		return glCreateShader(type);
	}

	void GlCompileShader(GLuint shader)
	{
		TRACE("[GLHelper::GlCompileShader]\n");
		glCompileShader(shader);
	}

	void GlGetShaderiv(GLuint shader, GLenum pname, GLint *params)
	{
		TRACE("[GLHelper::GlGetShaderiv]\n");
		glGetShaderiv(shader, pname, params);
	}

	void GlGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		TRACE("[GLHelper::GlGetShaderInfoLog]\n");
		glGetShaderInfoLog(shader, bufSize, length, infoLog);
	}

	void GlAttachShader(GLuint program, GLuint shader)
	{
		TRACE("[GLHelper::GlAttachShader]\n");
		glAttachShader(program, shader);
	}

	void GlLinkProgram(GLuint program)
	{
		TRACE("[GLHelper::GlLinkProgram]\n");
		glLinkProgram(program);
	}

	void GlGetProgramiv(GLuint program, GLenum pname, GLint *params)
	{
		TRACE("[GLHelper::GlGetProgramiv]\n");
		glGetProgramiv(program, pname, params);
	}

	void GlGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		TRACE("[GLHelper::GlGetProgramInfoLog]\n");
		glGetProgramInfoLog(program, bufSize, length, infoLog);
	}

	void GlGenTextures(GLsizei n, GLuint *textures)
	{
		TRACE("[GLHelper::GlGenTextures]\n");
		glGenTextures(n, textures);
	}

	void GlPixelStorei(GLenum pname, GLint param)
	{
		TRACE("[GLHelper::GlPixelStorei]\n");
		glPixelStorei(pname, param);
	}

	void GlTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
	{
		TRACE("[GLHelper::GlTexImage2D]\n");
		glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	}

	void GlDeleteTextures(GLsizei n, const GLuint *textures)
	{
		TRACE("[GLHelper::GlDeleteTextures]\n");
		glDeleteTextures(n, textures);
	}

	GLenum GlGetError()
	{
		TRACE("[GLHelper::GlGetError]\n");
		return glGetError();
	}

	void GlUniform4fv(GLint location, GLsizei count, const GLfloat *value)
	{
		TRACE("[GLHelper::GlUniform4fv]\n");
		glUniform4fv(location, count, value);
	}

	void GlUniform2fv(GLint location, GLsizei count, const GLfloat *value)
	{
		TRACE("[GLHelper::GlUniform2fv]\n");
		glUniform2fv(location, count, value);
	}

	void GlGenVertexArrays(GLsizei n, GLuint *arrays)
	{
		TRACE("[GLHelper::GlGenVertexArrays]\n");
		glGenVertexArrays(n, arrays);
	}

	void GlBindVertexArray(GLuint array)
	{
		TRACE("[GLHelper::GlBindVertexArray]\n");
		glBindVertexArray(array);
	}

	void GlDrawArrays(GLenum mode, GLint first, GLsizei count)
	{
		TRACE("[GLHelper::GlDrawArrays]\n");
		glDrawArrays(mode, first, count);
	}
}
