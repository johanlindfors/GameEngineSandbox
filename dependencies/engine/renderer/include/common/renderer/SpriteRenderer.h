#pragma once
#include "ISpriteRenderer.h"

namespace Engine {
	class SpriteRenderer : public ISpriteRenderer {
	public:
		SpriteRenderer();
		~SpriteRenderer();

		// Engine::ISpriteRenderer
        void Initialize() override;
		void UpdateWindowSize(GLsizei width, GLsizei height) override;
		void Clear() override;
		void DrawSprite(std::shared_ptr<Sprite> sprite) override;
        void DrawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point position) override;

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
}
