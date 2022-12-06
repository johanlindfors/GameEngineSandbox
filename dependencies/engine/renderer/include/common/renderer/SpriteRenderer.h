#pragma once
#include "ISpriteRenderer.h"
#include <vector>

namespace Engine {
	class SpriteRenderer : public ISpriteRenderer {
	public:
		SpriteRenderer();
		~SpriteRenderer();

		// Engine::ISpriteRenderer
		void UpdateWindowSize(GLsizei width, GLsizei height) override;
		void Clear() override;
		void DrawSprite(std::shared_ptr<Sprite> sprite) override;
		void DrawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point position) override;

	private:
		void InitializeShaders();
		void InitializeBuffers();
		void InitializeVertexBuffer();
		void InitializeUVBuffer();
		void AddUVs(int x1, int y1, int x2, int y2);

		GLuint mProgram;
		GLsizei mWindowWidth;
		GLsizei mWindowHeight;

		// Vertex shader parameters
		GLint mVertexAttribLocation;
		GLint mUVAttribLocation;
		GLint mWorldMatrix;
		GLint mProjectionMatrix;
		// GLint mTextureSizeUniformLocation;
		// GLint mScreenSizeUniformLocation;

		// Fragment shader parameters
		GLint mTextureUniformLocation;

		GLuint mVertexPositionBuffer;
		GLuint mVertexUVBuffer;
		std::vector<GLfloat> mUVVertices;
		bool mInitialized;
	};
}
