#include "GLHelper.h"
#include <vector>

using namespace std;

GLuint CompileShader(GLenum type, const string& source)
{
	GLuint shader = glCreateShader(type);

	const char* sourceArray[1] = { source.c_str() };
	glShaderSource(shader, 1, sourceArray, NULL);
	glCompileShader(shader);

	GLint compileResult;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == 0)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		vector<GLchar> infoLog(infoLogLength);
		glGetShaderInfoLog(shader, (GLsizei)infoLog.size(), NULL, infoLog.data());

		wstring errorMessage = wstring(L"Shader compilation failed: ");
		errorMessage += wstring(infoLog.begin(), infoLog.end());
	}

	return shader;
}

GLuint CompileProgram(const string& vsSource, const string& fsSource)
{
	GLuint program = glCreateProgram();

	if (program == 0)
	{
		//throw winrt::hresult_error(E_FAIL, winrt::hstring(L"Program creation failed"));
	}

	GLuint vs = CompileShader(GL_VERTEX_SHADER, vsSource);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

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
		glGetProgramInfoLog(program, (GLsizei)infoLog.size(), NULL, infoLog.data());

		wstring errorMessage = std::wstring(L"Program link failed: ");
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
void SetTexturePixels(Texture2D texture, GLubyte* pixels)
{
	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture.TextureIndex);
	glPixelStorei(GL_PACK_ALIGNMENT, texture.TextureIndex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, texture.TextureIndex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.Width, texture.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	CheckOpenGLError();
	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void DeleteTexture(GLuint textureId) {
	glDeleteTextures(1, &textureId);
}

void CheckOpenGLError() {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("OpenGL error %08x\n", err);
	}
}