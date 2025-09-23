#pragma once
// thirdparty
#include <entt/entity/registry.hpp>
// engine
// game
#include "game/Components.hpp"
#include "game/GameDefines.hpp"

struct RandomSystem
{
    void initialize(entt::registry &reg)
    {
        auto view = reg.view<TileTypeComponent>();
        auto tiles = view.size();
        
        for (auto entity : view)
        {
            reg.emplace<RandomComponent>(entity, 0);
        }
    }

    void update(entt::registry &reg)
    {
        // auto view = reg.view<DirectionComponent, SpriteComponent>();
        // for (auto entity : view)
        // {
        //     auto [direction, sprite] = view.get(entity);
        //     sprite.rotation = directionToAngle(direction.direction);
        // };
    }
};
