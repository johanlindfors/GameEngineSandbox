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

	// glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	// glEnableVertexAttribArray(mVertexAttribLocation);
	// glVertexAttribPointer(mVertexAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f); 
	// glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(mWindowWidth), 
    //     static_cast<float>(mWindowHeight), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(mProjectionMatrix, 1, false, glm::value_ptr(projection));
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(sprite->Position.m[0], sprite->Position.m[1], 0.0f)); 
	// model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    // model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 
    // model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    // model = glm::scale(model, glm::vec3(size, 1.0f));
	glUniformMatrix4fv(mWorldMatrix, 1, false, glm::value_ptr(model));
	
	// glBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	// glEnableVertexAttribArray(mUVAttribLocation);
	// glVertexAttribPointer(mUVAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(sprite->Texture.TextureIndex));

	// Set the sampler texture unit to 0
	glUniform1i(mTextureUniformLocation, 0);

  	glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

	// GLushort indices[] = { 0, 1, 3, 1, 2, 3 };
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void SpriteRenderer::InitializeShaders() {
	// Vertex Shader source
	const std::string vs = STRING
	(
		attribute vec4 vertex; // <vec2 position, vec2 texCoords>
		//attribute vec2 uv;
		
		uniform mat4 world;
		uniform mat4 projection;

		varying vec2 TexCoords;

		void main()
		{
			TexCoords = vertex.zw;
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
			gl_FragColor = vec4(texture2D(texture, TexCoords).xyz, 0.5);
		}
	);

	printf("[SpriteRenderer::InitializeShaders] About to compile program\n");
	// Set up the shader and its uniform/attribute locations.
	mProgram = CompileProgram(vs, fs);
	printf("[SpriteRenderer::InitializeShaders] Program %d compiled\n", mProgram);
	CheckOpenGLError();

	// // Vertex shader parameters
	mVertexAttribLocation = glGetAttribLocation(mProgram, "vertex");
	//mUVAttribLocation = glGetAttribLocation(mProgram, "uv");
	mWorldMatrix = glGetUniformLocation(mProgram, "world");
	mProjectionMatrix = glGetUniformLocation(mProgram, "projection");

	printf("[SpriteRenderer::InitializeShaders] mVertexAttribLocation: %d\n", mVertexAttribLocation);
	//printf("[SpriteRenderer::InitializeShaders] mUVAttribLocation: %d\n", mUVAttribLocation);
	printf("[SpriteRenderer::InitializeShaders] mWorldMatrix: %d\n", mWorldMatrix);
	printf("[SpriteRenderer::InitializeShaders] mProjectionMatrix: %d\n", mProjectionMatrix);

	// Fragment shader parameters
	mTextureUniformLocation = glGetUniformLocation(mProgram, "texture");
	printf("[SpriteRenderer::InitializeShaders] mTextureUniformLocation: %d\n", mTextureUniformLocation);
}

void SpriteRenderer::InitializeBuffers() {

    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	// GLfloat vertexPositions[] =
	// {
	// 	 0.0f, 1.0f, 0.0f, 1.0f,
	// 	 0.0f, 0.0f, 0.0f, 1.0f,
	// 	 1.0f, 0.0f, 0.0f, 1.0f,
	// 	 1.0f, 1.0f, 0.0f, 1.0f,
	// };

	// glGenBuffers(1, &mVertexPositionBuffer);
	// glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

	// GLfloat vertexUVs[] =
	// {
	// 	0.0f, 1.0f,
	// 	0.0f, 0.0f,
	// 	1.0f, 0.0f,
	// 	1.0f, 1.0f,
	// };

	// glGenBuffers(1, &mVertexUVBuffer);
	// glBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertexUVs), vertexUVs, GL_STATIC_DRAW);
}
