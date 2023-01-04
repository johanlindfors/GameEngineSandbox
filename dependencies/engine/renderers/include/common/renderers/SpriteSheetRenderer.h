#pragma once
#include "ISpriteRenderer.h"
#include <vector>
#include <string>
#include "resources/Shader.h"
#include "utilities/ILazyInitialized.h"

namespace Engine {

	class SpriteSheetRenderer : public ISpriteRenderer, public Utilities::ILazyInitialized {
	public:
		SpriteSheetRenderer(std::string filename);
		~SpriteSheetRenderer();

		// Engine::ISpriteRenderer
		void initialize() override;
		void updateWindowSize(int width, int height) override;
		void clear() override;
		void drawSprite(std::shared_ptr<Sprite> sprite) override;
		void drawSprite(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) override;
		
		// Utilities::ILazyInitialized
		void lazyInitialize() override;

		void loadSpriteSheet(std::string fileName);

	private:
		void initializeShaders();
		void initializeVertexBuffer();
		void initializeUVBuffer();
		void addUVs(int x1, int y1, int x2, int y2);

		std::string mFilename;
		std::shared_ptr<Shader> mShader;
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
