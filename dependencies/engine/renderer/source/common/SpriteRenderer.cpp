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
#include <vector>

#define STRING(s) #s

using namespace std;
using namespace Engine;
using namespace Utilities;

SpriteRenderer::SpriteRenderer()
	: mInitialized(false)
{
	InitializeShaders();
	InitializeBuffers();
}

#define BUFFER_OFFSET(i) ((void*)(i))

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
	this->DrawSprite(sprite, sprite->Position);
}

void SpriteRenderer::DrawSprite(shared_ptr<Sprite> sprite, Vector2 position)
{
	if(!mInitialized) {
		glUseProgram(mProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(2));
		glUniform1i(mTextureUniformLocation, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
		glEnableVertexAttribArray(mVertexAttribLocation);
		glVertexAttribPointer(mVertexAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		mInitialized = true;
	}

	glm::mat4 projection = glm::ortho(0.0f, (float)mWindowWidth, 0.0f, (float)mWindowHeight, -1.0f, 1.0f); 
	glUniformMatrix4fv(mProjectionMatrix, 1, false, glm::value_ptr(projection));

	glm::mat4 world = glm::mat4(1.0f);
	world= glm::translate(world, glm::vec3(position.m[0], position.m[1], 0.0f)); 
	if(sprite->Rotation != 0.0f) {
		world = glm::translate(world, glm::vec3(0.5f * sprite->Texture.Width, 0.5f * sprite->Texture.Height, 0.0f)); 
    	world = glm::rotate(world, glm::radians(sprite->Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    	world = glm::translate(world, glm::vec3(-0.5f * sprite->Texture.Width, -0.5f * sprite->Texture.Height, 0.0f));		
	}
    world = glm::scale(world, glm::vec3(sprite->Width, sprite->Height, 1.0f));
	glUniformMatrix4fv(mWorldMatrix, 1, false, glm::value_ptr(world));
	
	glBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	glEnableVertexAttribArray(mUVAttribLocation);
	glVertexAttribPointer(mUVAttribLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), BUFFER_OFFSET(sizeof(GL_FLOAT)*sprite->Offset*8));

	GLushort indices[] = { 0, 1, 3, 1, 2, 3 };
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
	// CheckOpenGLError();
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

void SpriteRenderer::InitializeBuffers() {
	InitializeVertexBuffer();
	InitializeUVBuffer();

    printf("[SpriteRenderer::InitializeBuffers] done\n");
}

void SpriteRenderer::InitializeVertexBuffer()
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
}

void SpriteRenderer::AddUVs(int x1, int y1, int x2, int y2)
{
	GLfloat width = 512.0;
	GLfloat height = 512.0;

	GLfloat s1 = x1 / width;
	GLfloat t1 = (height - y1) / height;
	GLfloat s2 = x2 / width;
	GLfloat t2 = (height - y2) / height;

	mUVVertices.push_back(s1);
	mUVVertices.push_back(t1);
	mUVVertices.push_back(s1);
	mUVVertices.push_back(t2);
	mUVVertices.push_back(s2);
	mUVVertices.push_back(t2);
	mUVVertices.push_back(s2);
	mUVVertices.push_back(t1);
}

void SpriteRenderer::InitializeUVBuffer() 
{
	AddUVs(1, 1, 35, 25); 		//  0 bird1
	AddUVs(35, 1, 69, 25); 		//  1 bird2
	AddUVs(69, 1, 103, 25); 	//  2 bird3
	AddUVs(1, 70, 2, 71); 		//  3 sky
	AddUVs(1, 26, 87, 68); 		//  4 city
	AddUVs(1, 70, 352, 103); 	//  5 clouds
	AddUVs(382, 2, 495, 104); 	//  6 instructions
	AddUVs(1, 105, 193, 153); 	//  7 gameover
	AddUVs(194, 105, 378, 157); //  8 getready
	AddUVs(2, 173, 46, 217); 	//  9 silver
	AddUVs(2, 221, 46, 265); 	// 10 gold
	AddUVs(53, 174, 278, 287); 	// 11 scoreboard
	AddUVs(2, 293, 106, 351); 	// 12 button
	AddUVs(116, 298, 295, 346); // 13 title
	AddUVs(2, 478, 417, 510); 	// 14 trees
	AddUVs(108, 1, 131, 27); 	// 15 ground
	AddUVs(402, 405, 454, 430); // 16 pipetop
	AddUVs(458, 110, 510, 135); // 17 pipebottom
	AddUVs(1, 102, 2, 103);		// 18 clouds background
	AddUVs(2, 509, 3, 510);		// 19 trees background
	AddUVs(108, 26, 109, 27);	// 20 ground background
	AddUVs(402, 110, 454, 120); // 21 pipe
	AddUVs(1, 364, 8, 371);		// 22 pink border

	glGenBuffers(1, &mVertexUVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, mUVVertices.size() * sizeof(GLfloat), &mUVVertices.front(), GL_STATIC_DRAW);
}
