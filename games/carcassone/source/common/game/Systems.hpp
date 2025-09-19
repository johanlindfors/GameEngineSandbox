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
        mSprite->tileSize = { TILE_WIDTH, TILE_HEIGHT };
        mSprite->size = { TILE_WIDTH, TILE_HEIGHT };
    }

    void setTexture(Engine::Texture2D texture)
    {
        mTexture = texture;
    }

    void updateScreenSize(int width, int height)
    {
        mScreenWidth = width;
        mScreenHeight = height;

        mSprite->size = { TILE_WIDTH, TILE_HEIGHT };
        mViewOffsetX = width / 2 - (mSprite->size.width / 2);
        mViewOffsetY = height / 2 - (mSprite->size.height / 2);
    }

    Utilities::Point<int> getViewOffset()
    {
        return {mMouseMoveOffsetX, mMouseMoveOffsetY};
    }

    void setMouseMoveOffset(int x, int y) {
        debuglog << "MX: " << x << " MY: " << y << std::endl;
    
        mMouseMoveOffsetX += x;
        mMouseMoveOffsetY -= y;
    }

    void update(entt::registry& reg) {
        // debuglog << "[SpriteSystem::update]" << std::endl;
        
        auto view = reg.view<SpriteComponent, PositionComponent>();
        for(auto entity : view) {
            auto [sprite, position] = view.get(entity);
            sprite.position.x = static_cast<float>(position.x * mScreenWidth / SCREEN_WIDTH);
            sprite.position.y = static_cast<float>(position.y * mScreenHeight / SCREEN_HEIGHT);
        };
    }

    void render(entt::registry& reg, std::shared_ptr<Engine::IRenderer> renderer) {
        // debuglog << "[SpriteSystem::render]" << std::endl;

        auto spriteRenderer = std::static_pointer_cast<Engine::SpriteRenderer>(renderer);

        auto view = reg.view<SpriteComponent>();
        for(auto entity : view) {
            auto sprite = view.get<SpriteComponent>(entity);
            mSprite->texture = mTexture;
            mSprite->setFrame(sprite.frame);
            spriteRenderer->drawSprite(mSprite, 
                { 
                    sprite.position.x + mViewOffsetX + mMouseMoveOffsetX, 
                    sprite.position.y + mViewOffsetY + mMouseMoveOffsetY
                }
            ); 
        };
    }
};
