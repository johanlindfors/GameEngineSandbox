#pragma once
#include "ISpriteRenderer.h"
#include <vector>
#include <string>

namespace Engine {

	class Shader;

	class SpriteSheetRenderer : public ISpriteRenderer {
	public:
		SpriteSheetRenderer(std::wstring filename);
		~SpriteSheetRenderer();

		// Engine::ISpriteRenderer
		void Initialize() override;
		void UpdateWindowSize(GLsizei width, GLsizei height) override;
		void Clear() override;
		void DrawSprite(std::shared_ptr<Sprite> sprite) override;
		void DrawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) override;
		
		void LoadSpriteSheet(std::wstring fileName);

	private:
		void InitializeShaders();
		void InitializeVertexBuffer();
		void InitializeUVBuffer();
		void AddUVs(int x1, int y1, int x2, int y2);

		std::wstring mFilename;
		std::unique_ptr<Shader> mShader;
		GLsizei mWindowWidth;
		GLsizei mWindowHeight;

		// Vertex shader parameters
		GLint mVertexAttribLocation;
		GLint mUVAttribLocation;

		GLuint mVertexPositionBuffer;
		GLuint mVertexUVBuffer;
		std::vector<GLfloat> mUVVertices;
		bool mInitialized;
	};
}
