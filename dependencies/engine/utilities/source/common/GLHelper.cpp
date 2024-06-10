#include "utilities/GLHelper.hpp"
#include "utilities/Logger.hpp"
#include <vector>
using namespace std;

static bool DEBUG_OPENGL = false;

namespace Engine
{

	GLuint compileShader(GLenum type, const string &source)
	{
		if(DEBUG_OPENGL) if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileShader] Compiling shader" << endl;

		const auto shader = GlCreateShader(type);

		if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileShader] Shader created" << endl;
		const char *sourceArray[1] = {source.c_str()};
		GlShaderSource(shader, 1, sourceArray, nullptr);
		GlCompileShader(shader);
		if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileShader] Shader compiled" << endl;

		checkOpenGLError();

		GLint compileResult;
		GlGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

		if (compileResult == 0)
		{
			GLint infoLogLength;
			GlGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			GlGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileShader] Compilation error in shader: '" << strInfoLog << "'" << endl;
			delete[] strInfoLog;
		}

		return shader;
	}

	GLuint compileProgram(const string &vsSource, const string &fsSource)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileProgram] Creating program" << endl;
		checkOpenGLError();
		const auto program = GlCreateProgram();
		if (program == 0)
		{
			if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileProgram] Failed to create program -- should exit!" << endl;
			checkOpenGLError();
		}
		else
		{
			if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileProgram] Program created" << endl;
		}

		const auto vs = compileShader(GL_VERTEX_SHADER, vsSource);
		if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileProgram] Vertex shader compiled" << endl;
		const auto fs = compileShader(GL_FRAGMENT_SHADER, fsSource);
		if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileProgram] Fragment shader compiled" << endl;

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
		if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileProgram] Program linked" << endl;

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
			if(DEBUG_OPENGL) debuglog << "[GLHelper::CompileProgram] Program link failed: " << errorMessage.c_str() << endl;
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
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GenerateTexture] TextureId: '" << textureId << "'" << endl;
		checkOpenGLError();
		return textureId;
	}

	// Need to be called on UI thread
	void setTexturePixels(int textureIndex, int width, int height, bool hasAlpha, GLubyte *pixels)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::SetTexturePixels]" << endl;
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
			if(DEBUG_OPENGL) debuglog << "OpenGL error " << err << endl;
			//exit(1);
			throw new runtime_error("OpenGL error");
		}
	}

	void GlDeleteBuffers(GLsizei n, const GLuint *buffers)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDeleteBuffers]" << endl;
		glDeleteBuffers(n, buffers);
	}

	void GlDeleteProgram(GLuint program)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDeleteProgram]" << endl;
		glDeleteProgram(program);
	}

	void GlDisableVertexAttribArray(GLuint index) 
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDisableVertexAttribArray]" << endl;
		glDisableVertexAttribArray(index);
	}

	void GlViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlViewport]" << endl;
		glViewport(x, y, width, height);
	}

	void GlClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlClearColor]" << endl;
		glClearColor(red, green, blue, alpha);
	}

	void GlClear(GLbitfield mask)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlClear]" << endl;
		glClear(mask);
	}

	void GlDisable(GLenum cap)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDisable]" << endl;
		glDisable(cap);
	}

	void GlActiveTexture(GLenum texture)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlActiveTexture]" << endl;
		glActiveTexture(texture);
	}

	void GlBindTexture(GLenum target, GLuint texture)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlBindTexture]" << endl;
		glBindTexture(target, texture);
	}

	void GlEnable(GLenum cap)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlEnable]" << endl;
		glEnable(cap);
	}

	void GlBlendFunc(GLenum sfactor, GLenum dfactor)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlBlendFunc]" << endl;
		glBlendFunc(sfactor, dfactor);
	}

	void GlTexParameteri(GLenum target, GLenum pname, GLint param)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlTexParameteri]" << endl;
		glTexParameteri(target, pname, param);
	}

	void GlBindBuffer(GLenum target, GLuint buffer)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlBindBuffer]" << endl;
		glBindBuffer(target, buffer);
	}

	void GlEnableVertexAttribArray(GLuint index)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlEnableVertexAttribArray]" << endl;
		glEnableVertexAttribArray(index);
	}

	void GlVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlVertexAttribPointer" << endl;
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	void GlDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDrawElements]" << endl;
		glDrawElements(mode, count, type, indices);
	}

	GLint GlGetAttribLocation(GLuint program, const GLchar *name)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGetAttribLocation]" << endl;
		return glGetAttribLocation(program, name);
	}

	void GlGenBuffers(GLsizei n, GLuint *buffers)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGenBuffers]" << endl;
		glGenBuffers(n, buffers);
	}

	void GlBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlBufferData]" << endl;
		glBufferData(target, size, data, usage);
	}

	GLint GlGetUniformLocation(GLuint program, const GLchar *name)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGetUniformLocation]" << endl;
		return glGetUniformLocation(program, name);
	}

	void GlUniform1i(GLint location, GLint v0)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlUniform1i]" << endl;
		glUniform1i(location, v0);
	}

	void GlUniform2f(GLint location, GLfloat v0, GLfloat v1)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlUniform2f]" << endl;
		glUniform2f(location, v0, v1);
	}

	void GlUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlUniform3f]" << endl;
		glUniform3f(location, v0, v1, v2);
	}

	void GlUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlUniform4f]" << endl;
		glUniform4f(location, v0, v1, v2, v3);
	}

	void GlUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlUniformMatrix4fv]" << endl;
		glUniformMatrix4fv(location, count, transpose, value);
	}

	void GlUseProgram(GLuint program)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlUseProgram]" << endl;
		glUseProgram(program);
	}

	void GlDeleteShader(GLuint shader)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDeleteShader]" << endl;
		glDeleteShader(shader);
	}

	void GlShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlShaderSource]" << endl;
		glShaderSource(shader, count, string, length);
	}

	GLint GlCreateProgram()
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlCreateProgram]" << endl;
		return glCreateProgram();
	}

	GLuint GlCreateShader(GLenum type)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlCreateShader]" << endl;
		return glCreateShader(type);
	}

	void GlCompileShader(GLuint shader)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlCompileShader]" << endl;
		glCompileShader(shader);
	}

	void GlGetShaderiv(GLuint shader, GLenum pname, GLint *params)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGetShaderiv]" << endl;
		glGetShaderiv(shader, pname, params);
	}

	void GlGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGetShaderInfoLog]" << endl;
		glGetShaderInfoLog(shader, bufSize, length, infoLog);
	}

	void GlAttachShader(GLuint program, GLuint shader)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlAttachShader]" << endl;
		glAttachShader(program, shader);
	}

	void GlLinkProgram(GLuint program)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlLinkProgram]" << endl;
		glLinkProgram(program);
	}

	void GlGetProgramiv(GLuint program, GLenum pname, GLint *params)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGetProgramiv]" << endl;
		glGetProgramiv(program, pname, params);
	}

	void GlGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGetProgramInfoLog]" << endl;
		glGetProgramInfoLog(program, bufSize, length, infoLog);
	}

	void GlGenTextures(GLsizei n, GLuint *textures)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGenTextures]" << endl;
		glGenTextures(n, textures);
	}

	void GlPixelStorei(GLenum pname, GLint param)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlPixelStorei]" << endl;
		glPixelStorei(pname, param);
	}

	void GlTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlTexImage2D]" << endl;
		glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	}

	void GlDeleteTextures(GLsizei n, const GLuint *textures)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDeleteTextures]" << endl;
		glDeleteTextures(n, textures);
	}

	GLenum GlGetError()
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGetError]" << endl;
		return glGetError();
	}

	void GlUniform4fv(GLint location, GLsizei count, const GLfloat *value)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlUniform4fv]" << endl;
		glUniform4fv(location, count, value);
	}

	void GlUniform2fv(GLint location, GLsizei count, const GLfloat *value)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlUniform2fv]" << endl;
		glUniform2fv(location, count, value);
	}

	void GlGenVertexArrays(GLsizei n, GLuint *arrays)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGenVertexArrays]" << endl;
		glGenVertexArrays(n, arrays);
	}

	void GlBindVertexArray(GLuint array)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlBindVertexArray]" << endl;
		glBindVertexArray(array);
	}

	void GlDrawArrays(GLenum mode, GLint first, GLsizei count)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDrawArrays]" << endl;
		glDrawArrays(mode, first, count);
	}

	void GlCullFace(GLenum mode)
	{
		if(DEBUG_OPENGL) debuglog << "[GlHelper::GlCullFace]" << endl;
		glCullFace(mode);
	}
	
    void GlBindFramebuffer(GLenum target, GLuint framebuffer) {
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlBindFramebuffer]" << endl;
		glBindFramebuffer(target, framebuffer);
	}

    void GlFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlFramebufferRenderbuffer]" << endl;
		glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	}

    void GlRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlRenderbufferStorage]" << endl;
		glRenderbufferStorage(target, internalformat, width, height);
	}

    void GlBindRenderbuffer(GLenum target, GLuint renderbuffer)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlBindRenderbuffer]" << endl;
		glBindRenderbuffer(target, renderbuffer);
	}

    void GlGenFramebuffers(GLsizei n, GLuint *ids)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGenFramebuffers]" << endl;
		glGenFramebuffers(n, ids);
	}

    void GlDeleteFramebuffers(GLsizei n, GLuint *framebuffers)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDeleteFramebuffers]" << endl;
		glDeleteFramebuffers(n, framebuffers);
	}

    void GlDeleteVertexArrays(GLsizei n, const GLuint *arrays)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDeleteVertexArrays]" << endl;
		glDeleteVertexArrays(n, arrays);
	}

	void GlDeleteRenderbuffers(GLsizei n, GLuint *renderbuffers)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlDeleteRenderbuffers]" << endl;
		glDeleteRenderbuffers(n, renderbuffers);
	}

    void GlFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlFramebufferTexture2D]" << endl;
		glFramebufferTexture2D(target, attachment, textarget, texture, level);
	}

    void GlGenRenderbuffers(GLsizei n, GLuint *renderbuffers)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlGenRenderbuffers]" << endl;
		glGenRenderbuffers(n, renderbuffers);
	}

	GLenum GlCheckFramebufferStatus(GLenum target)
	{
		if(DEBUG_OPENGL) debuglog << "[GLHelper::GlCheckFramebufferStatus]" << endl;
		return glCheckFramebufferStatus(target);
	}
}
