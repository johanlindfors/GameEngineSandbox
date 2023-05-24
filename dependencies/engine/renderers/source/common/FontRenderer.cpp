#include "renderers/FontRenderer.h"
#include "resources/IResourceManager.h"
#include <string>
#include "utilities/MathHelper.h"
#include "utilities/GLHelper.h"
#include "renderers/Sprite.h"
#include "filesystem/IFileSystem.h"
#include "utilities/IOC.hpp"
#include "File.h"
#include "resources/Shader.h"

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
	mCharacterSprite->texture.textureIndex = atlasTexture.textureIndex;
}

void FontRenderer::drawString(const string& str, Utilities::Point<float> centerPosition, float scale)
{
	auto dimensions = measureString(str);
	auto x = centerPosition.x - dimensions.size.width/2 * scale;
	auto y = centerPosition.y - dimensions.size.height/2 * scale;
	for(const auto& character : str) {
		auto characterToDraw = mCharacters[character];
		drawCharacter(character, Utilities::Rectangle<float>(x, y, characterToDraw.width * scale, characterToDraw.height * scale));
		x += characterToDraw.xAdvance * scale;
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
	auto characterToDraw = mCharacters[character];
	Utilities::Rectangle<float> spriteOffset(
		characterToDraw.xOffset / 512.0f,  characterToDraw.yOffset / 512.0f,
		characterToDraw.width / 512.0f,  characterToDraw.height / 512.0f
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
