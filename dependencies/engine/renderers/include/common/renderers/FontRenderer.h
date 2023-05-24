#pragma once
#include <vector>
#include <map>
#include <string>
#include "glwrapper.h"
#include "utilities/MathHelper.h"
#include "utilities/ILazyInitialized.h"
#include "SpriteRenderer.h"

namespace Engine {

	struct Character {
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
		: public SpriteRenderer {
	public:
		FontRenderer(
			const std::string& atlasFilename,
			std::shared_ptr<Engine::Shader> shader, 
			std::shared_ptr<Engine::OrthographicCamera> camera);
		~FontRenderer() = default;

		void initialize();
		void drawString(const std::string& str, Utilities::Point<float> centerPosition, float scale);

	private:
		void addCharacter(int id, int x, int y, int width, int height, int xoffset, int yoffset, int xadvance, int offset);
		void drawCharacter(char character, Utilities::Rectangle<float> rectangle);

		Utilities::Rectangle<float> measureString(const std::string& str);

        std::string mAtlasFilename;
		std::shared_ptr<Engine::Sprite> mCharacterSprite;
		std::map<char, Character> mCharacters;
		bool mInitialized;
	};
}
