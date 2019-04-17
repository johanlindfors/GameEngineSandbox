#pragma once
#include "ISpriteRenderer.h"

class SpriteRenderer : public ISpriteRenderer {
public:
    SpriteRenderer();
    ~SpriteRenderer();
    void UpdateWindowSize(GLsizei width, GLsizei height);
	void Clear();
    void DrawSprite(Sprite& sprite);

private:
	void InitializeShaders();
	void InitializeBuffers();

	GLuint mProgram;
	GLsizei mWindowWidth;
	GLsizei mWindowHeight;

	// Vertex shader parameters
	GLint mVertexAttribLocation;
	GLint mUVAttribLocation;
	GLint mSpriteRectUniformLocation;
	GLint mSpriteWorldUniformLocation;
	GLint mTextureSizeUniformLocation;
	GLint mScreenSizeUniformLocation;

	// Fragment shader parameters
	GLint mTextureUniformLocation;

	GLuint mVertexPositionBuffer;
	GLuint mVertexUVBuffer;
};