#pragma once
#include "ISpriteRenderer.h"
#include <vector>
#include <string>

namespace Engine {

	class Shader;

	class FontRenderer : public ISpriteRenderer {
	public:
		FontRenderer(std::string textureFilename, std::string atlasFilename);
		~FontRenderer();

		// Engine::ISpriteRenderer
		void Initialize() override;
		void UpdateWindowSize(GLsizei width, GLsizei height) override;
		void Clear() override;
		void DrawSprite(std::shared_ptr<Sprite> sprite) override;
		void DrawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) override;
		
	private:
		void InitializeShaders();
		void InitializeVertexBuffer();
		void InitializeUVBuffer();
		void AddUVs(int x1, int y1, int x2, int y2);

		std::string mTextureFilename;
        std::string mAtlasFilename;
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
