#include "Map.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Map::Map()
{
    printf("[Map::constructor]\n");
}

Map::~Map()
{
    printf("[Map::destructor]\n");
}

void Map::initialize()
{
    printf("[Map::initialize]\n");
}

void Map::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {

	}
}
