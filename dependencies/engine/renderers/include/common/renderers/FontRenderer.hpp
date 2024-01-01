#pragma once
#include <vector>
#include <map>
#include <string>
#include "utilities/glwrapper.hpp"
#include "utilities/MathHelper.hpp"
#include "SpriteRenderer.hpp"

namespace Engine
{

	struct Character
	{
		int characterCode;
		int uVOffset;
		float xOffset;
		float yOffset;
		int xAdvance;
		float width;
		float height;
	};

	class Shader;
	struct Sprite;

	class FontRenderer
		: public SpriteRenderer
	{
	public:
		FontRenderer(
			const std::string &atlasFilename,
			const std::string &textureFilename,
			std::shared_ptr<Engine::Shader> shader,
			std::shared_ptr<Engine::OrthographicCamera> camera);
		~FontRenderer() = default;

		enum class Alignment
		{
			Center,
			Left,
			Right
		};

		void initialize();
		void drawString(const std::string &str, Alignment alignment, Engine::Point<float> position, float scale);

	private:
		void addCharacter(int id, int x, int y, int width, int height, int xoffset, int yoffset, int xadvance, int offset);
		void drawCharacter(char character, Engine::Rectangle<float> rectangle);

		Engine::Rectangle<float> measureString(const std::string &str);

		std::string mAtlasFilename;
		std::string mTextureFilename;
		std::shared_ptr<Engine::Sprite> mCharacterSprite;
		std::map<char, Character> mCharacters;
		bool mInitialized;
	};
}
