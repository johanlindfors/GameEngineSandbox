#pragma once
#include "glwrapper.h"
#include "ISpriteRenderer.h"

namespace Engine {
	class SpriteRenderer : public ISpriteRenderer {
	public:
		SpriteRenderer() = default;
		~SpriteRenderer();

		// Engine::ISpriteRenderer
        void initialize() override;
		void updateWindowSize(int width, int height) override;
		void clear() override;
		void drawSprite(std::shared_ptr<Sprite> sprite) override;
        void drawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) override;

	private:
		void initializeShaders();
		void initializeBuffers();

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
}
