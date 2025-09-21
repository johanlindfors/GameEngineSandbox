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

struct SpriteSystem
{
    int mScreenWidth;
    int mScreenHeight;
    int mViewOffsetX;
    int mViewOffsetY;
    int mMouseMoveOffsetX = 0;
    int mMouseMoveOffsetY = 0;
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

    void updateScreenSize(int width, int height)
    {
        mScreenWidth = width;
        mScreenHeight = height;

        mSprite->size = {TILE_WIDTH, TILE_HEIGHT};
        mViewOffsetX = width / 2 - (mSprite->size.width / 2);
        mViewOffsetY = height / 2 - (mSprite->size.height / 2);
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

    // void update(entt::registry &reg)
    // {
    //     auto view = reg.view<SpriteComponent, PositionComponent>();
    //     for (auto entity : view)
    //     {
    //         auto [sprite, position] = view.get(entity);
    //         sprite.position.x = static_cast<float>(position.x);// * mScreenWidth / SCREEN_WIDTH);
    //         sprite.position.y = static_cast<float>(position.y);// * mScreenHeight / SCREEN_HEIGHT);
    //     };
    // }

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
            spriteRenderer->drawSprite(mSprite,
                                       {(float)position.x * TILE_WIDTH+ mViewOffsetX + mMouseMoveOffsetX,
                                        (float)position.y * TILE_HEIGHT + mViewOffsetY + mMouseMoveOffsetY});
        };
    }
};
