#pragma once
#include <vector>
#include <map>
#include <string>
#include "glwrapper.h"
#include "utilities/MathHelper.h"
#include "utilities/ILazyInitialized.h"

namespace Engine {

	struct Character {
		int CharacterCode;
		int UVOffset;
		int XOffset;
		int YOffset;
		int XAdvance;
		int Width;
		int Height;
	};

	class Shader;

	class FontRenderer : public Utilities::ILazyInitialized  {
	public:
		FontRenderer(const std::string& atlasFilename);
		~FontRenderer();

		void Initialize();
		void UpdateWindowSize(int width, int height);
		void Clear();
		void DrawString(const std::string& str, Utilities::Point<float> centerPosition, float scale);

		// ILazyInitialized
		void LazyInitialize() override;

	private:
		void InitializeShaders();
		void InitializeVertexBuffer();
		void InitializeUVBuffer();
		void AddCharacter(int id, int x, int y, int width, int height, int xoffset, int yoffset, int xadvance, int offset);
		void AddUVs(int x1, int y1, int x2, int y2);
		void DrawCharacter(int offset, Utilities::Rectangle rectangle);

		Utilities::Rectangle MeasureString(const std::string& str);

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
