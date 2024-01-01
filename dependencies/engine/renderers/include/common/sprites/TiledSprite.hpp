#pragma once
#include "sprites/Sprite.hpp"
#include <string>
#include <map>
#include "utilities/IStepTimer.hpp"

namespace Engine
{
	struct TiledSprite : public Sprite
	{
		Engine::Size<int> tileSize;
		unsigned int currentTile;

		unsigned int getCols();
		unsigned int getRows();
		void setFrame(int frame);
		Engine::Rectangle<float> calculateTileOffset();
	};
}
