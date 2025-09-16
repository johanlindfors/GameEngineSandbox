#include "utilities/GLHelper.hpp"
#include "utilities/Logger.hpp"
#include <vector>

#define DEBUG_OPENGL(false);

#if defined(_DEBUG) && (DEBUG_OPENGL == true) 
#define TRACE(x) debuglog << x << std::endl;
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
		TRACE("[GLHelper::CompileShader] Compiling shader");

		const auto shader = GlCreateShader(type);

		TRACE("[GLHelper::CompileShader] Shader created");
		const char *sourceArray[1] = {source.c_str()};
		GlShaderSource(shader, 1, sourceArray, nullptr);
		GlCompileShader(shader);
		TRACE("[GLHelper::CompileShader] Shader compiled");

		checkOpenGLError();

		GLint compileResult;
		GlGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

		if (compileResult == 0)
		{
			GLint infoLogLength;
			GlGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			GlGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			TRACE("[GLHelper::CompileShader] Compilation error in shader: '" << strInfoLog << "'");
			delete[] strInfoLog;
		}

		return shader;
	}

	GLuint compileProgram(const string &vsSource, const string &fsSource)
	{
		TRACE("[GLHelper::CompileProgram] Creating program");
		checkOpenGLError();
		const auto program = GlCreateProgram();
		if (program == 0)
		{
			TRACE("[GLHelper::CompileProgram] Failed to create program -- should exit!");
			checkOpenGLError();
		}
		else
		{
			TRACE("[GLHelper::CompileProgram] Program created");
		}

		const auto vs = compileShader(GL_VERTEX_SHADER, vsSource);
		TRACE("[GLHelper::CompileProgram] Vertex shader compiled");
		const auto fs = compileShader(GL_FRAGMENT_SHADER, fsSource);
		TRACE("[GLHelper::CompileProgram] Fragment shader compiled");

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
		TRACE("[GLHelper::CompileProgram] Program linked");

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
			TRACE("[GLHelper::CompileProgram] Program link failed: " << errorMessage.c_str());
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
		TRACE("[GLHelper::GenerateTexture] TextureId: '" << textureId << "'");
		checkOpenGLError();
		return textureId;
	}

	// Need to be called on UI thread
	void setTexturePixels(int textureIndex, int width, int height, bool hasAlpha, GLubyte *pixels)
	{
		TRACE("[GLHelper::SetTexturePixels]");
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
			TRACE("OpenGL error " << err);
			//exit(1);
			throw new runtime_error("OpenGL error");
		}
	}

	void GlDeleteBuffers(GLsizei n, const GLuint *buffers)
	{
		TRACE("[GLHelper::GlDeleteBuffers]");
		glDeleteBuffers(n, buffers);
	}

	void GlDeleteProgram(GLuint program)
	{
		TRACE("[GLHelper::GlDeleteProgram]");
		glDeleteProgram(program);
	}

	void GlDisableVertexAttribArray(GLuint index) 
	{
		TRACE("[GLHelper::GlDisableVertexAttribArray]");
		glDisableVertexAttribArray(index);
	}

	void GlViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		TRACE("[GLHelper::GlViewport]\n");
		// debuglog << "New viewport: X: " 
		// 		 << x << " Y: " 
		// 		 << y << " Width: " 
		// 		 << width << " Height: " 
		// 		 << height <<	std::endl;
		glViewport(x, y, width, height);
	}

	void GlClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		TRACE("[GLHelper::GlClearColor]");
		glClearColor(red, green, blue, alpha);
	}

	void GlClear(GLbitfield mask)
	{
		TRACE("[GLHelper::GlClear]");
		glClear(mask);
	}

	void GlDisable(GLenum cap)
	{
		TRACE("[GLHelper::GlDisable]");
		glDisable(cap);
	}

	void GlActiveTexture(GLenum texture)
	{
		TRACE("[GLHelper::GlActiveTexture]");
		glActiveTexture(texture);
	}

	void GlBindTexture(GLenum target, GLuint texture)
	{
		TRACE("[GLHelper::GlBindTexture]");
		glBindTexture(target, texture);
	}

	void GlEnable(GLenum cap)
	{
		TRACE("[GLHelper::GlEnable]");
		glEnable(cap);
	}

	void GlBlendFunc(GLenum sfactor, GLenum dfactor)
	{
		TRACE("[GLHelper::GlBlendFunc]");
		glBlendFunc(sfactor, dfactor);
	}

	void GlTexParameteri(GLenum target, GLenum pname, GLint param)
	{
		TRACE("[GLHelper::GlTexParameteri]");
		glTexParameteri(target, pname, param);
	}

	void GlBindBuffer(GLenum target, GLuint buffer)
	{
		TRACE("[GLHelper::GlBindBuffer]");
		glBindBuffer(target, buffer);
	}

	void GlEnableVertexAttribArray(GLuint index)
	{
		TRACE("[GLHelper::GlEnableVertexAttribArray]");
		glEnableVertexAttribArray(index);
	}

	void GlVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
	{
		TRACE("[GLHelper::GlVertexAttribPointer");
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	void GlDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
	{
		TRACE("[GLHelper::GlDrawElements]");
		glDrawElements(mode, count, type, indices);
	}

	GLint GlGetAttribLocation(GLuint program, const GLchar *name)
	{
		TRACE("[GLHelper::GlGetAttribLocation]");
		return glGetAttribLocation(program, name);
	}

	void GlGenBuffers(GLsizei n, GLuint *buffers)
	{
		TRACE("[GLHelper::GlGenBuffers]");
		glGenBuffers(n, buffers);
	}

	void GlBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
	{
		TRACE("[GLHelper::GlBufferData]");
		glBufferData(target, size, data, usage);
	}

	GLint GlGetUniformLocation(GLuint program, const GLchar *name)
	{
		TRACE("[GLHelper::GlGetUniformLocation]");
		return glGetUniformLocation(program, name);
	}

	void GlUniform1i(GLint location, GLint v0)
	{
		TRACE("[GLHelper::GlUniform1i]");
		glUniform1i(location, v0);
	}

	void GlUniform2f(GLint location, GLfloat v0, GLfloat v1)
	{
		TRACE("[GLHelper::GlUniform2f]");
		glUniform2f(location, v0, v1);
	}

	void GlUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		TRACE("[GLHelper::GlUniform3f]");
		glUniform3f(location, v0, v1, v2);
	}

	void GlUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		TRACE("[GLHelper::GlUniform4f]");
		glUniform4f(location, v0, v1, v2, v3);
	}

	void GlUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		TRACE("[GLHelper::GlUniformMatrix4fv]");
		glUniformMatrix4fv(location, count, transpose, value);
	}

	void GlUseProgram(GLuint program)
	{
		TRACE("[GLHelper::GlUseProgram]");
		glUseProgram(program);
	}

	void GlDeleteShader(GLuint shader)
	{
		TRACE("[GLHelper::GlDeleteShader]");
		glDeleteShader(shader);
	}

	void GlShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length)
	{
		TRACE("[GLHelper::GlShaderSource]");
		glShaderSource(shader, count, string, length);
	}

	GLint GlCreateProgram()
	{
		TRACE("[GLHelper::GlCreateProgram]");
		return glCreateProgram();
	}

	GLuint GlCreateShader(GLenum type)
	{
		TRACE("[GLHelper::GlCreateShader]");
		return glCreateShader(type);
	}

	void GlCompileShader(GLuint shader)
	{
		TRACE("[GLHelper::GlCompileShader]");
		glCompileShader(shader);
	}

	void GlGetShaderiv(GLuint shader, GLenum pname, GLint *params)
	{
		TRACE("[GLHelper::GlGetShaderiv]");
		glGetShaderiv(shader, pname, params);
	}

	void GlGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		TRACE("[GLHelper::GlGetShaderInfoLog]");
		glGetShaderInfoLog(shader, bufSize, length, infoLog);
	}

	void GlAttachShader(GLuint program, GLuint shader)
	{
		TRACE("[GLHelper::GlAttachShader]");
		glAttachShader(program, shader);
	}

	void GlLinkProgram(GLuint program)
	{
		TRACE("[GLHelper::GlLinkProgram]");
		glLinkProgram(program);
	}

	void GlGetProgramiv(GLuint program, GLenum pname, GLint *params)
	{
		TRACE("[GLHelper::GlGetProgramiv]");
		glGetProgramiv(program, pname, params);
	}

	void GlGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		TRACE("[GLHelper::GlGetProgramInfoLog]");
		glGetProgramInfoLog(program, bufSize, length, infoLog);
	}

	void GlGenTextures(GLsizei n, GLuint *textures)
	{
		TRACE("[GLHelper::GlGenTextures]");
		glGenTextures(n, textures);
	}

	void GlPixelStorei(GLenum pname, GLint param)
	{
		TRACE("[GLHelper::GlPixelStorei]");
		glPixelStorei(pname, param);
	}

	void GlTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
	{
		TRACE("[GLHelper::GlTexImage2D]");
		glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	}

	void GlDeleteTextures(GLsizei n, const GLuint *textures)
	{
		TRACE("[GLHelper::GlDeleteTextures]");
		glDeleteTextures(n, textures);
	}

	GLenum GlGetError()
	{
		TRACE("[GLHelper::GlGetError]");
		return glGetError();
	}

	void GlUniform4fv(GLint location, GLsizei count, const GLfloat *value)
	{
		TRACE("[GLHelper::GlUniform4fv]");
		glUniform4fv(location, count, value);
	}

	void GlUniform2fv(GLint location, GLsizei count, const GLfloat *value)
	{
		TRACE("[GLHelper::GlUniform2fv]");
		glUniform2fv(location, count, value);
	}

	void GlGenVertexArrays(GLsizei n, GLuint *arrays)
	{
		TRACE("[GLHelper::GlGenVertexArrays]");
		glGenVertexArrays(n, arrays);
	}

	void GlBindVertexArray(GLuint array)
	{
		TRACE("[GLHelper::GlBindVertexArray]");
		glBindVertexArray(array);
	}

	void GlDrawArrays(GLenum mode, GLint first, GLsizei count)
	{
		TRACE("[GLHelper::GlDrawArrays]");
		glDrawArrays(mode, first, count);
	}

    void GlBindFramebuffer(GLenum target, GLuint framebuffer) {
		TRACE("[GLHelper::GlBindFramebuffer]\n");
		glBindFramebuffer(target, framebuffer);
	}

	void GlCullFace(GLenum mode)
	{
		TRACE("[GlHelper::GlCullFace]");
		glCullFace(mode);
	}

    void GlFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	{
		TRACE("[GLHelper::GlFramebufferRenderbuffer]\n");
		glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	}

    void GlRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
	{
		TRACE("[GLHelper::GlRenderbufferStorage]\n");
		glRenderbufferStorage(target, internalformat, width, height);
	}

    void GlBindRenderbuffer(GLenum target, GLuint renderbuffer)
	{
		TRACE("[GLHelper::GlBindRenderbuffer]\n");
		glBindRenderbuffer(target, renderbuffer);
	}

    void GlGenFramebuffers(GLsizei n, GLuint *ids)
	{
		TRACE("[GLHelper::GlGenFramebuffers]\n");
		glGenFramebuffers(n, ids);
	}

    void GlDeleteFramebuffers(GLsizei n, GLuint *framebuffers)
	{
		TRACE("[GLHelper::GlDeleteFramebuffers]\n");
		glDeleteFramebuffers(n, framebuffers);
	}

    void GlDeleteVertexArrays(GLsizei n, const GLuint *arrays)
	{
		TRACE("[GLHelper::GlDeleteVertexArrays]\n");
		glDeleteVertexArrays(n, arrays);
	}

	void GlDeleteRenderbuffers(GLsizei n, GLuint *renderbuffers)
	{
		TRACE("[GLHelper::GlDeleteRenderbuffers]\n");
		glDeleteRenderbuffers(n, renderbuffers);
	}

    void GlFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
	{
		TRACE("[GLHelper::GlFramebufferTexture2D]\n");
		glFramebufferTexture2D(target, attachment, textarget, texture, level);
	}

    void GlGenRenderbuffers(GLsizei n, GLuint *renderbuffers)
	{
		TRACE("[GLHelper::GlGenRenderbuffers]\n");
		glGenRenderbuffers(n, renderbuffers);
	}

	GLenum GlCheckFramebufferStatus(GLenum target)
	{
		TRACE("[GLHelper::GlCheckFramebufferStatus]\n");
		return glCheckFramebufferStatus(target);
	}

	void GlPolygonMode(GLenum face, GLenum mode) 
	{
		TRACE("[GLHelper::GlPolygonMode]");
		glPolygonMode(face, mode);
	}
}
