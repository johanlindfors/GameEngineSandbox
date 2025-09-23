#pragma once
// thirdparty
#include <entt/entity/registry.hpp>
#include <memory>
#include <random>

// engine
#include "utilities/MathHelper.hpp"
#include "utilities/Logger.hpp"

// game
#include "game/Components.hpp"
#include "game/GameDefines.hpp"

struct PositionSystem
{
    int mScreenWidth;
    int mScreenHeight;
    int mViewOffsetX;
    int mViewOffsetY;
    int mMouseMoveOffsetX = 0;
    int mMouseMoveOffsetY = 0;

    void updateScreenSize(int width, int height)
    {
        mScreenWidth = width;
        mScreenHeight = height;

        mViewOffsetX = width / 2 - (TILE_WIDTH / 2);
        mViewOffsetY = height / 2 - (TILE_HEIGHT / 2);
    }

    Utilities::Point<int> getViewOffset()
    {
        return {mMouseMoveOffsetX, mMouseMoveOffsetY};
    }

    void setMouseMoveOffset(int x, int y)
    {
        mMouseMoveOffsetX += x;
        mMouseMoveOffsetY -= y;
    }

    void update(entt::registry &reg)
    {
        auto placedTilesView = reg.view<PositionComponent, SpriteComponent>();
        for (auto entity : placedTilesView)
        {
            auto [position, sprite] = placedTilesView.get(entity);
            sprite.position.x = (float)position.x * TILE_WIDTH + mViewOffsetX + mMouseMoveOffsetX;
            sprite.position.y = (float)position.y * TILE_HEIGHT + mViewOffsetY + mMouseMoveOffsetY;
        };

        auto validMovesView = reg.view<ValidMoveComponent, SpriteComponent>();
        for (auto entity : validMovesView)
        {
            auto [validMove, sprite] = validMovesView.get(entity);
            sprite.position.x = (float)validMove.x * TILE_WIDTH + mViewOffsetX + mMouseMoveOffsetX;
            sprite.position.y = (float)validMove.y * TILE_HEIGHT + mViewOffsetY + mMouseMoveOffsetY;
        };
    }
};
