#pragma once
// thirdparty
#include <entt/entity/registry.hpp>
#include <memory>
#include <random>

// engine
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
