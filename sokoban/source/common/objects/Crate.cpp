#include "Crate.hpp"
#include "utilities/IStepTimer.hpp"
#include "renderers/Sprite.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Crate::Crate(int x, int y)
{
    index = y * 10 + x;
    mSprite->position = { 
        static_cast<float>(x) * TILE_SIZE, 
        static_cast<float>(y) * TILE_SIZE
    };
    setFrame(3);
}
