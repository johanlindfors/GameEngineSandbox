#pragma once
// thirdparty
#include <memory>
#include <entt/entity/registry.hpp>
#include <random>

// engine
#include "input/IInputManager.hpp"
#include "sprites/TiledSprite.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/IOC.hpp"
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
        auto view = reg.view<PositionComponent, SpriteComponent>();
        for (auto entity : view)
        {
            auto [position, sprite] = view.get(entity);
            sprite.position.x = (float)position.x * TILE_WIDTH + mViewOffsetX + mMouseMoveOffsetX;
            sprite.position.y = (float)position.y * TILE_HEIGHT + mViewOffsetY + mMouseMoveOffsetY;
        };
    }
};

struct SpriteSystem
{
    Engine::Texture2D mTexture;
    std::shared_ptr<Engine::TiledSprite> mSprite;

    SpriteSystem()
        : mSprite(std::make_shared<Engine::TiledSprite>())
    {
        debuglog << "[Spritesystem::SpriteSystem] was created" << std::endl;
        mSprite->tileSize = {128, 128};
        mSprite->size = {TILE_WIDTH, TILE_HEIGHT};
    }

    void setTexture(Engine::Texture2D texture)
    {
        mTexture = texture;
    }

    float directionToAngle(Direction direction)
    {
        switch (direction)
        {
        case Direction::East:
            return 90.0f;
        case Direction::South:
            return 180.0f;
        case Direction::West:
            return 270.0f;
        case Direction::North:
        default:
            return 0.0f;
        }
    }

    void render(entt::registry &reg, std::shared_ptr<Engine::IRenderer> renderer)
    {
        auto spriteRenderer = std::static_pointer_cast<Engine::SpriteRenderer>(renderer);

        reg.sort<SpriteComponent>([](const SpriteComponent &lhs, const SpriteComponent &rhs) {
            return lhs.zOrder < rhs.zOrder;
        });
        auto view = reg.view<SpriteComponent, PositionComponent, DirectionComponent>();
        for (auto entity : view)
        {
            auto [sprite, position, direction] = view.get(entity);
            mSprite->texture = mTexture;
            mSprite->setFrame(sprite.frame);
            mSprite->rotation = directionToAngle(direction.direction);
            mSprite->rotationCenterPoint = {TILE_WIDTH / 2, TILE_HEIGHT / 2};
            spriteRenderer->drawSprite(mSprite, sprite.position);
        };
    }
};
