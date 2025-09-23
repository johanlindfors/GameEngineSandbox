#pragma once
// thirdparty
#include <entt/entity/registry.hpp>
#include <memory>
#include <random>

// engine
#include "input/IInputManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "resources/IResourceManager.hpp"
#include "sprites/TiledSprite.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"

// game
#include "game/Components.hpp"
#include "game/GameDefines.hpp"

struct TileSystem
{
    TileSystem(entt::registry &reg, bool useRiverExpansion = false)
    {
        // ...
        // .⌂.
        // ...
        for (auto i = 0; i < 4; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, Field, Field, Field, Field);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<CloisterComponent>(tile);
            reg.emplace<SpriteComponent>(tile, 0);
        }

        // ...
        // .⌂.
        // .║.
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, Field, Road, Field, Field);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<CloisterComponent>(tile);
            reg.emplace<SpriteComponent>(tile, 1);
        }
        
        // ...
        // ═══
        // ...
        for (auto i = 0; i < 8; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, Road, Field, Road, Road);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 2);
        }

        // ...
        // ═╗.
        // .║.
        for (auto i = 0; i < 9; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, Field, Road, Road, Road);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 3);
        }
        
        // ...
        // ═╦═
        // .║.
        for (auto i = 0; i < 4; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, Road, Road, Road, Road);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 4);
        }

        // .║.
        // ═╬═
        // .║.
        auto tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Road, Road, Road, Road, Road);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<SpriteComponent>(tile, 5);

        // ###
        // ...
        // ...
        for (auto i = 0; i < 5; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, Field, Field, Field, Field);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 6);
        }

        // ###
        // ═══
        // ...
        bool placeStartTile = true;
        for (auto i = 0; i < 4; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, Road, Field, Road, Road);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            if (placeStartTile && !useRiverExpansion)
            {
                reg.emplace<StartComponent>(tile);
                placeStartTile = false;
            }
            reg.emplace<SpriteComponent>(tile, 7);
        }

        // ###
        // ═╗.
        // .║.
        for (auto i = 0; i < 3; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, Field, Road, Road, Road);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 8);
        }

        // ###
        // .╔═
        // .║.
        for (auto i = 0; i < 3; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, Road, Road, Field, Road);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 9);
        }

        // ###
        // ═╦═
        // .║.
        for (auto i = 0; i < 3; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, Road, Road, Road, Road);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 10);
        }

        // #.#
        // ###
        // #.#
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Field, City, Field, City, City);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<SpriteComponent>(tile, 11);

        // ###
        // .##
        // ..#
        for (auto i = 0; i < 3; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, City, Field, Field, City);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 12);
        }

        // ###
        // ...
        // ###
        for (auto i = 0; i < 3; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, Field, City, Field, Field);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 13);
        }

        // ### This is a special case of the tile two steps above with discontinued cities
        // ..#
        // ..#
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, City, Field, Field, Field);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 14);
        }

        // ###
        // ═╗#
        // .║#
        for (auto i = 0; i < 3; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, City, Road, Road, Road);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 15);
        }

        // #.# badged
        // ###
        // #.#
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, City, Field, City, City);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<BadgeComponent>(tile);
            reg.emplace<SpriteComponent>(tile, 16);
        }

        // ### badged
        // .##
        // ..#
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, City, Field, Field, City);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<BadgeComponent>(tile);
            reg.emplace<SpriteComponent>(tile, 17);
        }

        // ### badged
        // ═╗#
        // .║#
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, City, Road, Road, Road);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<BadgeComponent>(tile);
            reg.emplace<SpriteComponent>(tile, 18);
        }

        // ###
        // ###
        // #.#
        for (auto i = 0; i < 3; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, City, Field, City, City);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 19);
        }

        // ###
        // ###
        // #║#
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, City, City, Road, City, City);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<SpriteComponent>(tile, 20);

        // ### badged
        // ###
        // #.#
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, City, City, Field, City, City);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<BadgeComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 21);

        // ### badged
        // ###
        // #║#
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, City, City, Road, City, City);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<BadgeComponent>(tile);
            reg.emplace<SpriteComponent>(tile, 22);
        }

        // ### badged
        // ###
        // ###
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, City, City, City, City, City);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<BadgeComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 21);

        if (!useRiverExpansion)
            return;

        // ... river source
        // .@@
        // ...
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Field, River, Field, Field, River);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<StartComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 27);

        // ###
        // @@@ 1st
        // ###
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, City, River, City, River, River);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<SpriteComponent>(tile, 99);

        // ...
        // @@@ 2st
        // ...
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, River, Field, River, River);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 99);
        }

        // .@. 1st
        // ═╗@
        // .║.
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, River, River, Road, Road, Road);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<SpriteComponent>(tile, 99);

        // ... 2st
        // @@.
        // .@.
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, Field, River, River, River);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<SpriteComponent>(tile, 99);
        }

        // ### 1st
        // @║@
        // .║.
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, City, River, Road, River, Road);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<SpriteComponent>(tile, 99);

        // #@. 1st
        // ##@
        // ###
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, River, River, City,City, City);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<SpriteComponent>(tile, 99);

        // .║. 1st
        // @║@
        // .║.
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Road, River, Road, River, Road);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<SpriteComponent>(tile, 99);

        // ... 1st
        // @⌂@
        // .║.
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Field, River, Road, River, Field);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<CloisterComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 99);

        // ... lake
        // @@.
        // ...
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Field, Field, Field, River, River);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<EndComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 99);
    }

    void update(entt::registry &reg)
    {
        // Update tile system components
    }
};

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

struct DirectionSystem
{
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

    void update(entt::registry &reg)
    {
        auto view = reg.view<DirectionComponent, SpriteComponent>();
        for (auto entity : view)
        {
            auto [direction, sprite] = view.get(entity);
            sprite.rotation = directionToAngle(direction.direction);
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

    void render(entt::registry &reg, std::shared_ptr<Engine::IRenderer> renderer)
    {
        auto spriteRenderer = std::static_pointer_cast<Engine::SpriteRenderer>(renderer);

        auto placedTilesView = reg.view<SpriteComponent, PositionComponent>();
        for (auto entity : placedTilesView)
        {
            auto sprite = placedTilesView.get<SpriteComponent>(entity);
            mSprite->texture = mTexture;
            mSprite->setFrame(sprite.frame);
            mSprite->rotation = sprite.rotation;
            mSprite->rotationCenterPoint = {TILE_WIDTH / 2, TILE_HEIGHT / 2};
            spriteRenderer->drawSprite(mSprite, sprite.position);
        };

        auto validMovesView = reg.view<SpriteComponent, ValidMoveComponent>();
        for (auto entity : validMovesView)
        {
            auto sprite = validMovesView.get<SpriteComponent>(entity);
            mSprite->texture = mTexture;
            mSprite->setFrame(sprite.frame);
            spriteRenderer->drawSprite(mSprite, sprite.position);
        };
    }
};
