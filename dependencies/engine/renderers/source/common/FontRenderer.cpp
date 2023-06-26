#include "renderers/FontRenderer.hpp"
#include "resources/IResourceManager.hpp"
#include <string>
#include "utilities/MathHelper.hpp"
#include "utilities/GLHelper.hpp"
#include "sprites/Sprite.hpp"
#include "filesystem/IFileSystem.hpp"
#include "utilities/IOC.hpp"
#include "filesystem/File.hpp"
#include "resources/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <vector>

#define STRING(s) #s
#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i))

using namespace std;
using namespace Engine;
using namespace Utilities;

FontRenderer::FontRenderer(const string& atlasFilename,
				std::shared_ptr<Engine::Shader> shader, 
				std::shared_ptr<Engine::OrthographicCamera> camera)
	: SpriteRenderer::SpriteRenderer(shader, camera)
	, mAtlasFilename(atlasFilename)
	, mCharacterSprite(make_shared<Sprite>())
	, mInitialized(false)
{ }

void FontRenderer::initialize() {
	SpriteRenderer::initialize();
	auto filesystem = IOCContainer::instance().resolve<IFileSystem>();
	auto file = filesystem->loadFile(mAtlasFilename, false);
	if(file->isOpen()) {
		int id, x, y, width, height, xoffset, yoffset, xadvance;
		char buffer[100];
		auto fileHandle = file->get();
		int offset = 0;
		while(!feof(fileHandle)) {
			auto readBytes = fscanf(fileHandle, "%d:%d,%d,%d,%d,%d,%d,%d", &id, &x, &y, &width, &height, &xoffset, &yoffset, &xadvance);
			if (readBytes > 0) {
				addCharacter(id, x, y, width, height, xoffset, yoffset, xadvance, offset++);
				auto ptr = fgets(buffer, 100, fileHandle); // skip the rest of the line
			}
		}
    }
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto atlasTexture = resourceManager->getTexture("atlas.png");
	mCharacterSprite->texture = atlasTexture;
	mInitialized = true;
}

void FontRenderer::drawString(const string& str, Utilities::Point<float> centerPosition, float scale)
{
	auto dimensions = measureString(str);
	auto x = centerPosition.x - dimensions.size.width/2 * scale;
	auto y = centerPosition.y - dimensions.size.height/2 * scale;
	for(const auto& character : str) {
		drawCharacter(character, Utilities::Rectangle<float>(
			x, 
			y, 
			mCharacters[character].width * scale,
			mCharacters[character].height * scale));
		x += mCharacters[character].xAdvance * scale;
	}
}

Utilities::Rectangle<float> FontRenderer::measureString(const string& str) 
{
	auto dimensions = Utilities::Rectangle<float>({ 0.0f, 0.0f, 0.0f, 63.0f });
	for(const auto& character : str) {
		dimensions.size.width += mCharacters[character].xAdvance;
	}
	return dimensions;
}

void FontRenderer::drawCharacter(char character, Utilities::Rectangle<float> rectangle)
{
	Utilities::Rectangle<float> spriteOffset(
		mCharacters[character].xOffset / 512.0f, mCharacters[character].yOffset / 512.0f,
		mCharacters[character].width / 512.0f, mCharacters[character].height / 512.0f
	);
	mCharacterSprite->offset = spriteOffset;
	mCharacterSprite->size = rectangle.size;
 	SpriteRenderer::drawSprite(mCharacterSprite, rectangle.position);
}

void FontRenderer::addCharacter(int id, int x, int y, int width, int height, int xoffset, int yoffset, int xadvance, int offset)
{	
	auto character = Character();
	character.characterCode = id;
	character.uVOffset = offset;
	character.xAdvance = xadvance;
	character.xOffset = static_cast<float>(x);
	character.yOffset = (512.0f - (y + height));
	character.width = static_cast<float>(width);
	character.height = static_cast<float>(height);

	mCharacters[(char)id] = character; 
}
