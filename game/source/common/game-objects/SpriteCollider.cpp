#include "SpriteCollider.h"

using std::shared_ptr;
using Engine::Sprite;

bool SpriteCollider::CollidesOnPosition(shared_ptr<Sprite> sprite1, shared_ptr<Sprite> sprite2) const
{
	int x1 = static_cast<int>(sprite1->Position.m[0]);
	int x2 = static_cast<int>(sprite2->Position.m[0]);
	int y1 = static_cast<int>(sprite1->Position.m[1]);
	int y2 = static_cast<int>(sprite2->Position.m[1]);
    return ( x1 == x2 && y1 == y2);
}