#include "renderer/SpriteRenderer.h"
#include <string>
#include "MathHelper.h"
#include "GLHelper.h"
#include "renderer/Sprite.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>

#define STRING(s) #s

using namespace std;
using namespace Engine;
using namespace Utilities;

SpriteRenderer::SpriteRenderer()
{
	InitializeShaders();
	InitializeBuffers();
}

SpriteRenderer::~SpriteRenderer()
{
	if (mProgram != 0)
	{
		glDeleteProgram(mProgram);
		mProgram = 0;
	}

	if (mVertexPositionBuffer != 0)
	{
		glDeleteBuffers(1, &mVertexPositionBuffer);
		mVertexPositionBuffer = 0;
	}

	if (mVertexUVBuffer != 0)
	{
		glDeleteBuffers(1, &mVertexUVBuffer);
		mVertexUVBuffer = 0;
	}
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::UpdateWindowSize(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	mWindowWidth = width;
	mWindowHeight = height;
}

void SpriteRenderer::Clear() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void SpriteRenderer::DrawSprite(shared_ptr<Sprite> sprite)
{
	CheckOpenGLError();
	glUseProgram(mProgram);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	glEnableVertexAttribArray(mVertexAttribLocation);
	glVertexAttribPointer(mVertexAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	glm::mat4 projection = glm::ortho(0.0f, (float)mWindowWidth, 0.0f, (float)mWindowHeight, -1.0f, 1.0f); 
	glUniformMatrix4fv(mProjectionMatrix, 1, false, glm::value_ptr(projection));

	glm::mat4 world = glm::mat4(1.0f);
	world= glm::translate(world, glm::vec3(sprite->Position.m[0], sprite->Position.m[1], 0.0f)); 
	if(sprite->Rotation != 0.0f) {
		world = glm::translate(world, glm::vec3(0.5f * sprite->Texture.Width, 0.5f * sprite->Texture.Height, 0.0f)); 
    	world = glm::rotate(world, glm::radians(sprite->Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    	world = glm::translate(world, glm::vec3(-0.5f * sprite->Texture.Width, -0.5f * sprite->Texture.Height, 0.0f));		
	}
    world = glm::scale(world, glm::vec3(sprite->Width, sprite->Height, 1.0f));
	glUniformMatrix4fv(mWorldMatrix, 1, false, glm::value_ptr(world));
	
	glBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	glEnableVertexAttribArray(mUVAttribLocation);
	glVertexAttribPointer(mUVAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(sprite->Texture.TextureIndex));

	// Set the sampler texture unit to 0
	glUniform1i(mTextureUniformLocation, 0);

	GLushort indices[] = { 0, 1, 3, 1, 2, 3 };
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
	CheckOpenGLError();
}

void SpriteRenderer::InitializeShaders() {
	// Vertex Shader source
	const std::string vs = STRING
	(
		attribute vec4 vertex; // <vec2 position, vec2 texCoords>
		attribute vec2 a_uv;
		
		uniform mat4 world;
		uniform mat4 projection;

		varying vec2 TexCoords;

		void main()
		{
			TexCoords = a_uv;
			gl_Position = projection * world * vertex;
		}
	);

	// Fragment Shader source
	const std::string fs = STRING
	(
		precision mediump float;
		varying vec2 TexCoords;

		uniform sampler2D texture;
		
		void main()
		{
			gl_FragColor = texture2D(texture, TexCoords);
		}
	);

	printf("[SpriteRenderer::InitializeShaders] About to compile program\n");
	// Set up the shader and its uniform/attribute locations.
	mProgram = CompileProgram(vs, fs);
	printf("[SpriteRenderer::InitializeShaders] Program %d compiled\n", mProgram);
	CheckOpenGLError();

	// // Vertex shader parameters
	mVertexAttribLocation = glGetAttribLocation(mProgram, "vertex");
	mUVAttribLocation = glGetAttribLocation(mProgram, "a_uv");
	mWorldMatrix = glGetUniformLocation(mProgram, "world");
	mProjectionMatrix = glGetUniformLocation(mProgram, "projection");

	printf("[SpriteRenderer::InitializeShaders] mVertexAttribLocation: %d\n", mVertexAttribLocation);
	printf("[SpriteRenderer::InitializeShaders] mUVAttribLocation: %d\n", mUVAttribLocation);
	printf("[SpriteRenderer::InitializeShaders] mWorldMatrix: %d\n", mWorldMatrix);
	printf("[SpriteRenderer::InitializeShaders] mProjectionMatrix: %d\n", mProjectionMatrix);

	// Fragment shader parameters
	mTextureUniformLocation = glGetUniformLocation(mProgram, "texture");
	printf("[SpriteRenderer::InitializeShaders] mTextureUniformLocation: %d\n", mTextureUniformLocation);
}

void SpriteRenderer::InitializeBuffers()
{
	GLfloat vertexPositions[] =
	{
		 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, 1.0f, 0.0f, 1.0f,
	};

	glGenBuffers(1, &mVertexPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

	GLfloat vertexUVs[] =
	{
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};

	glGenBuffers(1, &mVertexUVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexUVs), vertexUVs, GL_STATIC_DRAW);

    printf("[SpriteRenderer::InitializeBuffers] done\n");
}
