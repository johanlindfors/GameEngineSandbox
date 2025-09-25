#pragma once
// thirdparty
#include <entt/entity/registry.hpp>
#include <memory>

// engine
#include "renderers/SpriteRenderer.hpp"
#include "sprites/TiledSprite.hpp"
#include "utilities/Logger.hpp"
#include "utilities/MathHelper.hpp"

// game
#include "game/Components.hpp"
#include "game/GameDefines.hpp"

struct SpriteSystem
{
    std::shared_ptr<Engine::TiledSprite> mSprite;

    SpriteSystem()
        : mSprite(std::make_shared<Engine::TiledSprite>())
    {
        debuglog << "[Spritesystem::SpriteSystem] was created" << std::endl;
        mSprite->tileSize = {32, 32};
        mSprite->size = {TILE_WIDTH, TILE_HEIGHT};
        mSprite->rotationCenterPoint = {TILE_WIDTH / 2, TILE_HEIGHT / 2};
    }

    void setTexture(Engine::Texture2D texture)
    {
        mSprite->texture = texture;
    }

    void render(entt::registry &reg, std::shared_ptr<Engine::IRenderer> renderer, entt::entity currentTile, Utilities::Point<float> currentTilePosition)
    {
        auto spriteRenderer = std::static_pointer_cast<Engine::SpriteRenderer>(renderer);

        auto placedTilesView = reg.view<SpriteComponent, PositionComponent>();
        for (auto entity : placedTilesView)
        {
            auto sprite = placedTilesView.get<SpriteComponent>(entity);
            mSprite->setFrame(sprite.frame);
            mSprite->rotation = sprite.rotation;
            spriteRenderer->drawSprite(mSprite, sprite.position);
        };

        auto validMovesView = reg.view<SpriteComponent, ValidMoveComponent>();
        for (auto entity : validMovesView)
        {
            auto sprite = validMovesView.get<SpriteComponent>(entity);
            mSprite->setFrame(sprite.frame);
            spriteRenderer->drawSprite(mSprite, sprite.position);
        };

        // TODO: Draw next tile
        auto sprite = reg.view<SpriteComponent>().get<SpriteComponent>(currentTile);
        mSprite->setFrame(sprite.frame);
        spriteRenderer->drawSprite(mSprite, currentTilePosition);
    }
};
