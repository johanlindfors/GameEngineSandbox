#pragma once
// thirdparty
#include <entt/entity/registry.hpp>
// engine
// game
#include "game/Components.hpp"
#include "game/GameDefines.hpp"

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
