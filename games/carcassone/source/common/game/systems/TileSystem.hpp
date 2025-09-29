#pragma once
// thirdparty
#include <entt/entity/registry.hpp>
// engine
#include "utilities/Logger.hpp"
// game
#include "game/Components.hpp"
#include "game/GameDefines.hpp"

struct TileSystem
{
    bool mRiverExpansionEnabled;

    TileSystem(entt::registry &reg, bool useRiverExpansion = false)
    {
        mRiverExpansionEnabled = useRiverExpansion;
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
            if (placeStartTile && !mRiverExpansionEnabled)
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

        if (!mRiverExpansionEnabled)
            return;

        // ... river source
        // .@@
        // ...
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Field, River, Field, Field, River);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<RiverExpansionComponent>(tile);
        reg.emplace<StartComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 24);

        // ###
        // @@@ 1st
        // ###
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, City, River, City, River, River);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<RiverExpansionComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 25);

        // ...
        // @@@ 2st
        // ...
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, River, Field, River, River);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<RiverExpansionComponent>(tile);
            reg.emplace<SpriteComponent>(tile, 26);
        }

        // .@. 1st
        // ═╗@
        // .║.
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, River, River, Road, Road, Road);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<RiverExpansionComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 27);

        // ... 2st
        // @@.
        // .@.
        for (auto i = 0; i < 2; i++)
        {
            auto tile = reg.create();
            reg.emplace<TileTypeComponent>(tile, Field, Field, River, River, River);
            reg.emplace<DirectionComponent>(tile, Direction::North);
            reg.emplace<RiverExpansionComponent>(tile);
            reg.emplace<SpriteComponent>(tile, 28);
        }

        // ### 1st
        // @║@
        // .║.
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, City, River, Road, River, Road);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<RiverExpansionComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 29);

        // #@. 1st
        // ##@
        // ###
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, River, River, City,City, City);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<RiverExpansionComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 30);

        // .║. 1st
        // @║@
        // .║.
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Road, River, Road, River, Road);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<RiverExpansionComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 31);

        // ... 1st
        // @⌂@
        // .║.
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Field, River, Road, River, Field);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<RiverExpansionComponent>(tile);
        reg.emplace<CloisterComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 32);

        // ... lake
        // @@.
        // ...
        tile = reg.create();
        reg.emplace<TileTypeComponent>(tile, Field, Field, Field, River, River);
        reg.emplace<DirectionComponent>(tile, Direction::North);
        reg.emplace<RiverExpansionComponent>(tile);
        reg.emplace<EndComponent>(tile);
        reg.emplace<SpriteComponent>(tile, 33);
    }

    entt::entity getNextRiverTile(entt::registry &reg) 
    {
        entt::entity entity = entt::null;
        int tilesToPlace = 0;
        auto tilesToPlaceView = reg.view<RiverExpansionComponent>(entt::exclude<PositionComponent, EndComponent>);
        for(auto tile: tilesToPlaceView) {
            tilesToPlace++;
        }
        int random_tile = rand() % tilesToPlace;
        int counter = 0;
        if( tilesToPlace > 0) {
            for(auto tile: tilesToPlaceView) {
                if(counter++ == random_tile) {
                    debuglog << "Selected tile " << random_tile << " of " << tilesToPlace << " remaining." << std::endl;
                    entity = tile;
                    break;
                }
            }
        } else {
            debuglog << "Selected the end river tile!" << std::endl;
            // No more river tiles to place, disable river expansion and return the end tile
            mRiverExpansionEnabled = false;
            entity = reg.view<RiverExpansionComponent, EndComponent>().front();
        }
        return entity;
    }

    entt::entity getNextTile(entt::registry &reg) 
    {
        entt::entity entity = reg.view<StartComponent>().front();
        if(entity != entt::null)
        {
            return entity;
        }
        
        if(mRiverExpansionEnabled)
        {
            return getNextRiverTile(reg);
        }

        int tilesToPlace = 0;
        auto tilesToPlaceView = reg.view<TileTypeComponent>(entt::exclude<PositionComponent, EndComponent>);
        for(auto tile: tilesToPlaceView) {
            tilesToPlace++;
        }
        if(tilesToPlace > 1)
        {
            int random_tile = rand() % tilesToPlace;
            int counter = 0;
            for(auto tile: tilesToPlaceView) {
                if(counter++ == random_tile) {
                    debuglog << "Selected tile " << random_tile << " of " << tilesToPlace << " remaining.\n";
                    entity = tile;
                    break;
                }
            }
        } else {
            entity = tilesToPlaceView.front();
        }
        return entity;
    }

    void update(entt::registry &reg)
    {
        // Update tile system components
    }
};
