#include "utilities/GLHelper.hpp"
#include "utilities/Logger.hpp"
#include <vector>
using namespace std;

namespace Engine
{

	GLuint compileShader(GLenum type, const string &source)
	{
		debuglog << "[GLHelper::CompileShader] Compiling shader" << endl;

		const auto shader = GlCreateShader(type);

		debuglog << "[GLHelper::CompileShader] Shader created" << endl;
		const char *sourceArray[1] = {source.c_str()};
		GlShaderSource(shader, 1, sourceArray, nullptr);
		GlCompileShader(shader);
		debuglog << "[GLHelper::CompileShader] Shader compiled" << endl;

		checkOpenGLError();

		GLint compileResult;
		GlGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

		if (compileResult == 0)
		{
			GLint infoLogLength;
			GlGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			GlGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			debuglog << "Compilation error in shader: '" << strInfoLog << "'" << endl;
			delete[] strInfoLog;
		}

		return shader;
	}

	GLuint compileProgram(const string &vsSource, const string &fsSource)
	{
		debuglog << "[GLHelper::CompileProgram] Creating program" << endl;
		checkOpenGLError();
		const auto program = GlCreateProgram();
		if (program == 0)
		{
			debuglog << "[GLHelper::CompileProgram] Failed to create program -- should exit!" << endl;
			checkOpenGLError();
		}
		else
		{
			debuglog << "[GLHelper::CompileProgram] Program created" << endl;
		}

		const auto vs = compileShader(GL_VERTEX_SHADER, vsSource);
		debuglog << "[GLHelper::CompileProgram] Vertex shader compiled\n" << endl;
		const auto fs = compileShader(GL_FRAGMENT_SHADER, fsSource);
		debuglog << "[GLHelper::CompileProgram] Fragment shader compiled" << endl;

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
		debuglog << "[GLHelper::CompileProgram] Program linked" << endl;

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
			debuglog << "Program link failed: " << errorMessage.c_str() << endl;
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
		debuglog << "[GLHelper::GenerateTexture] TextureId: '" << textureId << "'" << endl;
		checkOpenGLError();
		return textureId;
	}

	// Need to be called on UI thread
	void setTexturePixels(int textureIndex, int width, int height, bool hasAlpha, GLubyte *pixels)
	{
		debuglog << "[GLHelper::SetTexturePixels]" << endl;
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
			debuglog << "OpenGL error " << err << endl;
			exit(1);
		}
	}

	void GlDeleteBuffers(GLsizei n, const GLuint *buffers)
	{
		debuglog << "[GLHelper::GlDeleteBuffers]" << endl;
		glDeleteBuffers(n, buffers);
	}

	void GlDeleteProgram(GLuint program)
	{
		debuglog << "[GLHelper::GlDeleteProgram]" << endl;
		glDeleteProgram(program);
	}

	void GlDisableVertexAttribArray(GLuint index) 
	{
		debuglog << "[GLHelper::GlDisableVertexAttribArray]" << endl;
		glDisableVertexAttribArray(index);
	}

	void GlViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		debuglog << "[GLHelper::GlViewport]" << endl;
		glViewport(x, y, width, height);
	}

	void GlClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		debuglog << "[GLHelper::GlClearColor]" << endl;
		glClearColor(red, green, blue, alpha);
	}

	void GlClear(GLbitfield mask)
	{
		debuglog << "[GLHelper::GlClear]" << endl;
		glClear(mask);
	}

	void GlDisable(GLenum cap)
	{
		debuglog << "[GLHelper::GlDisable]" << endl;
		glDisable(cap);
	}

	void GlActiveTexture(GLenum texture)
	{
		debuglog << "[GLHelper::GlActiveTexture]" << endl;
		glActiveTexture(texture);
	}

	void GlBindTexture(GLenum target, GLuint texture)
	{
		debuglog << "[GLHelper::GlBindTexture]" << endl;
		glBindTexture(target, texture);
	}

	void GlEnable(GLenum cap)
	{
		debuglog << "[GLHelper::GlEnable]" << endl;
		glEnable(cap);
	}

	void GlBlendFunc(GLenum sfactor, GLenum dfactor)
	{
		debuglog << "[GLHelper::GlBlendFunc]" << endl;
		glBlendFunc(sfactor, dfactor);
	}

	void GlTexParameteri(GLenum target, GLenum pname, GLint param)
	{
		debuglog << "[GLHelper::GlTexParameteri]" << endl;
		glTexParameteri(target, pname, param);
	}

	void GlBindBuffer(GLenum target, GLuint buffer)
	{
		debuglog << "[GLHelper::GlBindBuffer]" << endl;
		glBindBuffer(target, buffer);
	}

	void GlEnableVertexAttribArray(GLuint index)
	{
		debuglog << "[GLHelper::GlEnableVertexAttribArray]" << endl;
		glEnableVertexAttribArray(index);
	}

	void GlVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
	{
		debuglog << "[GLHelper::GlVertexAttribPointern" << endl;
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	void GlDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
	{
		debuglog << "[GLHelper::GlDrawElements]" << endl;
		glDrawElements(mode, count, type, indices);
	}

	GLint GlGetAttribLocation(GLuint program, const GLchar *name)
	{
		debuglog << "[GLHelper::GlGetAttribLocation]" << endl;
		return glGetAttribLocation(program, name);
	}

	void GlGenBuffers(GLsizei n, GLuint *buffers)
	{
		debuglog << "[GLHelper::GlGenBuffers]" << endl;
		glGenBuffers(n, buffers);
	}

	void GlBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
	{
		debuglog << "[GLHelper::GlBufferData]" << endl;
		glBufferData(target, size, data, usage);
	}

	GLint GlGetUniformLocation(GLuint program, const GLchar *name)
	{
		debuglog << "[GLHelper::GlGetUniformLocation]" << endl;
		return glGetUniformLocation(program, name);
	}

	void GlUniform1i(GLint location, GLint v0)
	{
		debuglog << "[GLHelper::GlUniform1i]" << endl;
		glUniform1i(location, v0);
	}

	void GlUniform2f(GLint location, GLfloat v0, GLfloat v1)
	{
		debuglog << "[GLHelper::GlUniform2f]" << endl;
		glUniform2f(location, v0, v1);
	}

	void GlUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		debuglog << "[GLHelper::GlUniform3f]" << endl;
		glUniform3f(location, v0, v1, v2);
	}

	void GlUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		debuglog << "[GLHelper::GlUniform4f]" << endl;
		glUniform4f(location, v0, v1, v2, v3);
	}

	void GlUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		debuglog << "[GLHelper::GlUniformMatrix4fv]" << endl;
		glUniformMatrix4fv(location, count, transpose, value);
	}

	void GlUseProgram(GLuint program)
	{
		debuglog << "[GLHelper::GlUseProgram]" << endl;
		glUseProgram(program);
	}

	void GlDeleteShader(GLuint shader)
	{
		debuglog << "[GLHelper::GlDeleteShader]" << endl;
		glDeleteShader(shader);
	}

	void GlShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length)
	{
		debuglog << "[GLHelper::GlShaderSource]" << endl;
		glShaderSource(shader, count, string, length);
	}

	GLint GlCreateProgram()
	{
		debuglog << "[GLHelper::GlCreateProgram]" << endl;
		return glCreateProgram();
	}

	GLuint GlCreateShader(GLenum type)
	{
		debuglog << "[GLHelper::GlCreateShader]" << endl;
		return glCreateShader(type);
	}

	void GlCompileShader(GLuint shader)
	{
		debuglog << "[GLHelper::GlCompileShader]" << endl;
		glCompileShader(shader);
	}

	void GlGetShaderiv(GLuint shader, GLenum pname, GLint *params)
	{
		debuglog << "[GLHelper::GlGetShaderiv]" << endl;
		glGetShaderiv(shader, pname, params);
	}

	void GlGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		debuglog << "[GLHelper::GlGetShaderInfoLog]" << endl;
		glGetShaderInfoLog(shader, bufSize, length, infoLog);
	}

	void GlAttachShader(GLuint program, GLuint shader)
	{
		debuglog << "[GLHelper::GlAttachShader]" << endl;
		glAttachShader(program, shader);
	}

	void GlLinkProgram(GLuint program)
	{
		debuglog << "[GLHelper::GlLinkProgram]" << endl;
		glLinkProgram(program);
	}

	void GlGetProgramiv(GLuint program, GLenum pname, GLint *params)
	{
		debuglog << "[GLHelper::GlGetProgramiv]\n" << endl;
		glGetProgramiv(program, pname, params);
	}

	void GlGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		debuglog << "[GLHelper::GlGetProgramInfoLog]" << endl;
		glGetProgramInfoLog(program, bufSize, length, infoLog);
	}

	void GlGenTextures(GLsizei n, GLuint *textures)
	{
		debuglog << "[GLHelper::GlGenTextures]" << endl;
		glGenTextures(n, textures);
	}

	void GlPixelStorei(GLenum pname, GLint param)
	{
		debuglog << "[GLHelper::GlPixelStorei]" << endl;
		glPixelStorei(pname, param);
	}

	void GlTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
	{
		debuglog << "[GLHelper::GlTexImage2D]" << endl;
		glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	}

	void GlDeleteTextures(GLsizei n, const GLuint *textures)
	{
		debuglog << "[GLHelper::GlDeleteTextures]" << endl;
		glDeleteTextures(n, textures);
	}

	GLenum GlGetError()
	{
		debuglog << "[GLHelper::GlGetError]" << endl;
		return glGetError();
	}

	void GlUniform4fv(GLint location, GLsizei count, const GLfloat *value)
	{
		debuglog << "[GLHelper::GlUniform4fv]" << endl;
		glUniform4fv(location, count, value);
	}

	void GlUniform2fv(GLint location, GLsizei count, const GLfloat *value)
	{
		debuglog << "[GLHelper::GlUniform2fv]" << endl;
		glUniform2fv(location, count, value);
	}

	void GlGenVertexArrays(GLsizei n, GLuint *arrays)
	{
		debuglog << "[GLHelper::GlGenVertexArrays]" << endl;
		glGenVertexArrays(n, arrays);
	}

	void GlBindVertexArray(GLuint array)
	{
		debuglog << "[GLHelper::GlBindVertexArray]" << endl;
		glBindVertexArray(array);
	}

	void GlDrawArrays(GLenum mode, GLint first, GLsizei count)
	{
		debuglog << "[GLHelper::GlDrawArrays]" << endl;
		glDrawArrays(mode, first, count);
	}

	void GlCullFace(GLenum mode)
	{
		debuglog << "[GlHelper::GlCullFace]" << endl;
		glCullFace(mode);
	}
}
