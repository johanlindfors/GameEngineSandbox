#pragma once
#include "Sprite.hpp"
#include <string>
#include <map>
#include "utilities/IStepTimer.hpp"

namespace Engine
{
	struct TiledSprite : public Sprite
    {
		Utilities::Size<int> tileSize;
		unsigned int currentTile;

		unsigned int getCols() {
			return texture.width / tileSize.width;
		}

		unsigned int getRows() {
			return texture.height / tileSize.height;
		}

		void setFrame(int frame) {
			currentTile = frame;
			calculateTileOffset();
		}

		Utilities::Rectangle<float> calculateTileOffset() {
			Utilities::Size<float> normalizedTileSize = {
				static_cast<float>(tileSize.width) / texture.width,
				static_cast<float>(tileSize.height) / texture.height
			};
			offset = {
				static_cast<float>(currentTile % getCols() * normalizedTileSize.width),
				1.0f - static_cast<float>(static_cast<int>(currentTile / getCols() + 1) * normalizedTileSize.height),
				normalizedTileSize.width,
				normalizedTileSize.height
			};
			return offset;
		}
	};
}
