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
            static_cast<float>(tileSize.width) / texture.width,
            static_cast<float>(tileSize.height) / texture.height};
        offset = {
            static_cast<float>(currentTile % getCols() * normalizedTileSize.width),
            1.0f - static_cast<float>(static_cast<int>(currentTile / getCols() + 1) * normalizedTileSize.height),
            normalizedTileSize.width,
            normalizedTileSize.height};
        return offset;
    }
}