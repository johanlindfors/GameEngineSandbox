#include "Map.hpp"
#include "renderers/SpriteRenderer.hpp"

using namespace std;
using namespace Engine;

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

}

void Map::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {

	}
}
