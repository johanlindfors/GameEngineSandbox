#include "GLHelper.h"
#include <vector>

using namespace std;

namespace Engine {

	GLuint CompileShader(GLenum type, const string& source)
	{
		const auto shader = glCreateShader(type);

		const char* sourceArray[1] = { source.c_str() };
		glShaderSource(shader, 1, sourceArray, nullptr);
		glCompileShader(shader);

		GLint compileResult;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

		if (compileResult == 0)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			vector<GLchar> infoLog(infoLogLength);
			glGetShaderInfoLog(shader, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());

			wstring errorMessage(L"Shader compilation failed: ");
			errorMessage += wstring(infoLog.begin(), infoLog.end());
		}

		return shader;
	}

	GLuint CompileProgram(const string& vsSource, const string& fsSource)
	{
		const auto program = glCreateProgram();

		if (program == 0)
		{
			//throw winrt::hresult_error(E_FAIL, winrt::hstring(L"Program creation failed"));
		}

		const auto vs = CompileShader(GL_VERTEX_SHADER, vsSource);
		const auto fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

		if (vs == 0 || fs == 0)
		{
			glDeleteShader(fs);
			glDeleteShader(vs);
			glDeleteProgram(program);
			return 0;
		}

		glAttachShader(program, vs);
		glDeleteShader(vs);

		glAttachShader(program, fs);
		glDeleteShader(fs);

		glLinkProgram(program);

		GLint linkStatus;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		CheckOpenGLError();

		if (linkStatus == 0)
		{
			GLint infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			vector<GLchar> infoLog(infoLogLength);
			glGetProgramInfoLog(program, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());

			wstring errorMessage(L"Program link failed: ");
			errorMessage += wstring(infoLog.begin(), infoLog.end());
		}

		return program;
	}

	// Needs to be called on UI thread
	GLuint GenerateTexture()
	{
		// Texture object handle
		GLuint textureId = 0;
		// Generate a texture object
		glGenTextures(1, &textureId);
		CheckOpenGLError();
		return textureId;
	}

	// Need to be called on UI thread
	void SetTexturePixels(int textureIndex, int width, int height, GLubyte* pixels)
	{
		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(textureIndex));
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		CheckOpenGLError();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		CheckOpenGLError();
		// Set the filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void DeleteTexture(int textureIndex) {
		auto glTextureIndex = static_cast<GLuint>(textureIndex);
		glDeleteTextures(1, &glTextureIndex);
	}

	void CheckOpenGLError() {
		const auto err = glGetError();
		if (err != GL_NO_ERROR) {
			printf("OpenGL error %08x\n", err);
		}
	}
}
