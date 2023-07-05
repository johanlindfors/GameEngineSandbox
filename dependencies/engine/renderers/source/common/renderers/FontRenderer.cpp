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
				const string& textureFilename,
				shared_ptr<Shader> shader, 
				shared_ptr<OrthographicCamera> camera)
	: SpriteRenderer::SpriteRenderer(shader, camera)
	, mAtlasFilename(atlasFilename)
	, mTextureFilename(textureFilename)
	, mCharacterSprite(make_shared<Sprite>())
	, mInitialized(false)
{ }

void FontRenderer::initialize() {
	SpriteRenderer::initialize();

	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto atlasTexture = resourceManager->getTexture(mTextureFilename);
	mCharacterSprite->texture = atlasTexture;

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
	mInitialized = true;
}

void FontRenderer::drawString(const string& str, Alignment alignment, Point<float> position, float scale)
{
	auto dimensions = measureString(str);
	float x, y;
	y = position.y - dimensions.size.height/2 * scale;
		
	switch (alignment)
	{
	case Alignment::Center:
		x = position.x - dimensions.size.width/2 * scale;
		break;

	case Alignment::Left:
		x = position.x;
		break;
	
	case Alignment::Right:
		x = position.x - dimensions.size.width * scale;
		break;

	default:
		break;
	}
	for(const auto& character : str) {
		drawCharacter(character, Rectangle<float>(
			x, 
			y, 
			mCharacters[character].width * scale,
			mCharacters[character].height * scale));
		x += mCharacters[character].xAdvance * scale;
	}
}

Rectangle<float> FontRenderer::measureString(const string& str) 
{
	auto dimensions = Rectangle<float>({ 0.0f, 0.0f, 0.0f, 0.0f });
	for(const auto& character : str) {
		dimensions.size.width += mCharacters[character].xAdvance;
		if(mCharacters[character].height > dimensions.size.height){
			dimensions.size.height = mCharacters[character].height;
		}
	}
	return dimensions;
}

void FontRenderer::drawCharacter(char character, Rectangle<float> rectangle)
{
	const auto textureWidth = mCharacterSprite->texture.width;
	const auto textureHeight = mCharacterSprite->texture.height;
	Rectangle<float> spriteOffset(
		mCharacters[character].xOffset / textureWidth, mCharacters[character].yOffset / textureHeight,
		mCharacters[character].width / textureWidth, mCharacters[character].height / textureHeight
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
	character.yOffset = (mCharacterSprite->texture.height - (y + height));
//	character.yOffset = static_cast<float>(y);
	character.width = static_cast<float>(width);
	character.height = static_cast<float>(height);

	mCharacters[(char)id] = character; 
}
