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
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"

// game
#include "game/Components.hpp"
#include "game/GameDefines.hpp"

struct SpriteSystem 
{
	int mScreenWidth;
    int mScreenHeight;
	std::shared_ptr<Engine::TiledSprite> mSprite;

    SpriteSystem()
        : mSprite(std::make_shared<Engine::TiledSprite>())
    {
        debuglog << "[Spritesystem::SpriteSystem] was created" << std::endl;
        mSprite->tileSize = { 32, 32 };
        mSprite->size = { 128.0f, 128.0f };
    }

    void updateScreenSize(int width, int height) {
        mScreenWidth = width;
        mScreenHeight = height;

        mSprite->size = { 128.0f, 128.0f };
    }

    void update(entt::registry& reg) {
        debuglog << "[SpriteSystem::update]" << std::endl;
        
        auto view = reg.view<SpriteComponent, PositionComponent>();
        for(auto entity : view) {
            auto [sprite, position] = view.get(entity);
            sprite.position.x = static_cast<float>(position.x * mScreenWidth / SCREEN_WIDTH);
            sprite.position.y = static_cast<float>(position.y * mScreenHeight / SCREEN_HEIGHT);
        };
    }

    void render(entt::registry& reg, std::shared_ptr<Engine::IRenderer> renderer) {
        debuglog << "[SpriteSystem::render]" << std::endl;

        auto spriteRenderer = std::static_pointer_cast<Engine::SpriteRenderer>(renderer);

        auto view = reg.view<SpriteComponent>();
        for(auto entity : view) {
            auto sprite = view.get<SpriteComponent>(entity);
            mSprite->texture = sprite.texture;
            mSprite->setFrame(sprite.frame);
            spriteRenderer->drawSprite(mSprite, sprite.position); 
        };
    }
};
