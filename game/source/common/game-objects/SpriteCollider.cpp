#include "SpriteCollider.h"

using std::shared_ptr;
using Engine::Sprite;

bool SpriteCollider::CollidesOnPosition(shared_ptr<Sprite> sprite1, shared_ptr<Sprite> sprite2) const
{
    return (sprite1->Position.m[0] == sprite2->Position.m[0] && 
			sprite1->Position.m[1] == sprite2->Position.m[1]);
}