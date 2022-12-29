#pragma once
#include "IRenderer.h"

namespace Engine {
	class SimpleRenderer : public IRenderer {
	public:
		SimpleRenderer() = default;
		~SimpleRenderer() = default;

		// Engine::IRenderer
        void Initialize() override;
		void UpdateWindowSize(int width, int height) override;
		void Clear() override;
		// void Draw(std::shared_ptr<Sprite> sprite) override;
        // void Draw(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) override;

	private:
		// void InitializeShaders();
		// void InitializeBuffers();

		// GLuint mProgram;
		// GLsizei mWindowWidth;
		// GLsizei mWindowHeight;

		// // Vertex shader parameters
		// GLint mVertexAttribLocation;
		// GLint mUVAttribLocation;
		// GLint mSpriteRectUniformLocation;
		// GLint mSpriteWorldUniformLocation;
		// GLint mTextureSizeUniformLocation;
		// GLint mScreenSizeUniformLocation;

		// // Fragment shader parameters
		// GLint mTextureUniformLocation;

		// GLuint mVertexPositionBuffer;
		// GLuint mVertexUVBuffer;
	};
}
