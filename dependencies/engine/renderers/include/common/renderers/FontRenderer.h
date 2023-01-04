#pragma once
#include <vector>
#include <map>
#include <string>
#include "glwrapper.h"
#include "utilities/MathHelper.h"
#include "utilities/ILazyInitialized.h"

namespace Engine {

	struct Character {
		int characterCode;
		int uVOffset;
		int xOffset;
		int yOffset;
		int xAdvance;
		int width;
		int height;
	};

	class Shader;

	class FontRenderer : public Utilities::ILazyInitialized  {
	public:
		FontRenderer(const std::string& atlasFilename);
		~FontRenderer();

		void initialize();
		void updateWindowSize(int width, int height);
		void clear();
		void drawString(const std::string& str, Utilities::Point<float> centerPosition, float scale);

		// ILazyInitialized
		void lazyInitialize() override;

	private:
		void initializeShaders();
		void initializeVertexBuffer();
		void initializeUVBuffer();
		void addCharacter(int id, int x, int y, int width, int height, int xoffset, int yoffset, int xadvance, int offset);
		void addUVs(int x1, int y1, int x2, int y2);
		void drawCharacter(int offset, Utilities::Rectangle rectangle);

		Utilities::Rectangle measureString(const std::string& str);

        std::string mAtlasFilename;
		std::shared_ptr<Shader> mShader;
		GLsizei mWindowWidth;
		GLsizei mWindowHeight;

		// Vertex shader parameters
		GLint mVertexAttribLocation;
		GLint mUVAttribLocation;

		GLuint mVertexPositionBuffer;
		GLuint mVertexUVBuffer;
		std::vector<GLfloat> mUVVertices;
		std::map<char, Character> mCharacters;
		bool mInitialized;
	};
}
