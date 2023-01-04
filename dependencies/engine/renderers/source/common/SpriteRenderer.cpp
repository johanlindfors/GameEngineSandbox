#include "renderers/SpriteRenderer.h"
#include <string>
#include "utilities/MathHelper.h"
#include "utilities/GLHelper.h"
#include "renderers/Sprite.h"

#define STRING(s) #s

using namespace std;
using namespace Engine;
using namespace Utilities;

void SpriteRenderer::initialize()
{
	initializeShaders();
	initializeBuffers();
}

SpriteRenderer::~SpriteRenderer()
{
	if (mProgram != 0)
	{
		GlDeleteProgram(mProgram);
		mProgram = 0;
	}

	if (mVertexPositionBuffer != 0)
	{
		GlDeleteBuffers(1, &mVertexPositionBuffer);
		mVertexPositionBuffer = 0;
	}

	if (mVertexUVBuffer != 0)
	{
		GlDeleteBuffers(1, &mVertexUVBuffer);
		mVertexUVBuffer = 0;
	}
}

void SpriteRenderer::updateWindowSize(int width, int height)
{
	GlViewport(0, 0, width, height);
	mWindowWidth = width;
	mWindowHeight = height;
}

void SpriteRenderer::clear() {
	GlClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GlClear(GL_COLOR_BUFFER_BIT);
}

void SpriteRenderer::drawSprite(shared_ptr<Sprite> sprite)
{
    drawSprite(sprite, sprite->position);
}

void SpriteRenderer::drawSprite(shared_ptr<Sprite> sprite, Point<float> position)
{
	//printf("[SpriteRenderer::DrawSprite] Id: %d Program: %d\n", sprite->Texture.TextureIndex, mProgram);
	checkOpenGLError();
	GlUseProgram(mProgram);

	GlEnable(GL_BLEND);
	GlBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GlBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	GlEnableVertexAttribArray(mVertexAttribLocation);
	GlVertexAttribPointer(mVertexAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	//printf("[SpriteRenderer::DrawSprite] Width : %d\n", sprite->Width);
	//printf("[SpriteRenderer::DrawSprite] Height: %d\n", sprite->Height);
	Vector4 spriteRect{0.0f, 0.0f, static_cast<float>(sprite->width), static_cast<float>(sprite->height)};
	GlUniform4fv(mSpriteRectUniformLocation, 1, &(spriteRect.idx[0]));
	// CheckOpenGLError();
    auto vector = Vector2{position.x, position.y};
	GlUniform2fv(mSpriteWorldUniformLocation, 1, &(vector.idx[0]));

	Vector2 screenSize{static_cast<float>(mWindowWidth), static_cast<float>(mWindowHeight)};
	GlUniform2fv(mScreenSizeUniformLocation, 1, &(screenSize.idx[0]));

	GlBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	GlEnableVertexAttribArray(mUVAttribLocation);
	GlVertexAttribPointer(mUVAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	Vector2 textureSize{static_cast<float>(sprite->texture.width), static_cast<float>(sprite->texture.height)};
	GlUniform2fv(mTextureSizeUniformLocation, 1, &(textureSize.idx[0]));

	GlActiveTexture(GL_TEXTURE0);
	GlBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(sprite->texture.textureIndex));
	// Set the sampler texture unit to 0
	GlUniform1i(mTextureUniformLocation, 0);

	GLushort indices[] = { 0, 1, 3, 1, 2, 3 };
	GlDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
	//printf("[SpriteRenderer::DrawSprite] End\n");
}

void SpriteRenderer::initializeShaders() {
	// Vertex Shader source
	const std::string vs = STRING
	(
		//the incoming vertex' position
		attribute vec4 a_position;
		//and its texture coordinate
		attribute vec2 a_uv;
		uniform vec2 screenSize;
		// array that contains information on
		// sprite
		// [0] -> spriteSourceX
		// [1] -> spriteSourceY
		// [2] -> spriteWidth
		// [3] -> spriteHeight
		uniform vec4 spriteRect;

		// a vec2 that represents sprite position in the world
		// [0] -> spriteX
		// [1] -> spriteY
		uniform vec2 spriteWorld;

		// texture width and height
		uniform vec2 textureSize;

		//the varying statement tells the shader pipeline that this variable
		//has to be passed on to the next stage (so the fragment shader)
		varying vec2 v_uv;

		//the shader entry point is the main method
		void main()
		{
			gl_Position = a_position; //copy the position

			// adjust position according to
			// sprite width and height
			gl_Position.x = ((gl_Position.x * spriteRect[2]) + spriteWorld[0]) / (screenSize[0] / 2.0);
			gl_Position.y = ((-gl_Position.y * spriteRect[3]) - spriteWorld[1]) / (screenSize[1] / 2.0);

			// coordinates are being written
			// in homogeneous space, we have
			// to translate the space origin
			// to upper-left corner
			gl_Position.x -= 1.0;
			gl_Position.y += 1.0;

			// (texCoordX  * spriteWidth / textureWidth) + texSourceX
			v_uv.x = (a_uv.x ) + spriteRect[0] / textureSize[0];
			// inverting v component
			v_uv.y = ((1.0 - a_uv.y)) + spriteRect[1] / textureSize[1];
		}
	);

	// Fragment Shader source
	const std::string fs = STRING
	(
#ifndef __APPLE__
		precision mediump float;
#endif
		//incoming values from the vertex shader stage.
		//if the vertices of a primitive have different values, they are interpolated!
		varying vec2 v_uv;
		uniform sampler2D texture;

		void main()
		{
			// read the fragment color from texture
			gl_FragColor = texture2D(texture, v_uv);
		}
	);

	printf("[SpriteRenderer::InitializeShaders] About to compile program\n");
	// Set up the shader and its uniform/attribute locations.
	mProgram = compileProgram(vs, fs);
	printf("[SpriteRenderer::InitializeShaders] Program %d compiled\n", mProgram);
	checkOpenGLError();

	// // Vertex shader parameters
	mVertexAttribLocation = GlGetAttribLocation(mProgram, "a_position");
	mUVAttribLocation = GlGetAttribLocation(mProgram, "a_uv");
	mScreenSizeUniformLocation = GlGetUniformLocation(mProgram, "screenSize");
	mSpriteRectUniformLocation = GlGetUniformLocation(mProgram, "spriteRect");
	mSpriteWorldUniformLocation = GlGetUniformLocation(mProgram, "spriteWorld");
	mTextureSizeUniformLocation = GlGetUniformLocation(mProgram, "textureSize");

	printf("[SpriteRenderer::InitializeShaders] mVertexAttribLocation: %d\n", mVertexAttribLocation);
	printf("[SpriteRenderer::InitializeShaders] mUVAttribLocation: %d\n", mUVAttribLocation);
	printf("[SpriteRenderer::InitializeShaders] mScreenSizeUniformLocation: %d\n", mScreenSizeUniformLocation);
	printf("[SpriteRenderer::InitializeShaders] mSpriteRectUniformLocation: %d\n", mSpriteRectUniformLocation);
	printf("[SpriteRenderer::InitializeShaders] mSpriteWorldUniformLocation: %d\n", mSpriteWorldUniformLocation);
	printf("[SpriteRenderer::InitializeShaders] mTextureSizeUniformLocation: %d\n", mTextureSizeUniformLocation);

	// Fragment shader parameters
	mTextureUniformLocation = GlGetUniformLocation(mProgram, "texture");
	printf("[SpriteRenderer::InitializeShaders] mTextureUniformLocation: %d\n", mTextureUniformLocation);
}

void SpriteRenderer::initializeBuffers() {
	GLfloat vertexPositions[] =
	{
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 0.0f,
		 1.0f, 0.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,
	};

	GlGenBuffers(1, &mVertexPositionBuffer);
	GlBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	GlBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

	GLfloat vertexUVs[] =
	{
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};

	GlGenBuffers(1, &mVertexUVBuffer);
	GlBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	GlBufferData(GL_ARRAY_BUFFER, sizeof(vertexUVs), vertexUVs, GL_STATIC_DRAW);
}
