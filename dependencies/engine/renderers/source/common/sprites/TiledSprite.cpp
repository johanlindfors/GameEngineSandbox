#include "sprites/TiledSprite.hpp"

using namespace Utilities;

namespace Engine
{
    unsigned int TiledSprite::getCols()
    {
        return texture.width / tileSize.width;
    }

    unsigned int TiledSprite::getRows()
    {
        return texture.height / tileSize.height;
    }

    void TiledSprite::setFrame(int frame)
    {
        currentTile = frame;
        calculateTileOffset();
    }

    Rectangle<float> TiledSprite::calculateTileOffset()
    {
        Size<float> normalizedTileSize = {
            1.0f / getCols(),
            1.0f / getRows()
        };
        offset = {
            currentTile % getCols() * normalizedTileSize.width,
            1.0f - (currentTile / getCols() + 1) * normalizedTileSize.height,
            normalizedTileSize.width,
            normalizedTileSize.height};
        return offset;
    }
}