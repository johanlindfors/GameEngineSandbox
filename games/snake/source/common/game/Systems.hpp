#pragma once
// thirdparty
#include <memory>
#include <entt/entity/registry.hpp>

// engine
#include "input/IInputManager.hpp"
#include "sprites/Sprite.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "resources/IResourceManager.hpp"

// game
#include "game/Components.hpp"
#include "game/GameDefines.hpp"

struct transform_system {
    void update(entt::registry& reg) {
        auto view = reg.view<position_component, direction_component>(entt::exclude<static_component>);
        for(auto entity : view) {
            auto [position, direction] = view.get(entity);
            position.x = (position.x + direction.x + SCREEN_SIZE) % SCREEN_SIZE;
            position.y = (position.y + direction.y + SCREEN_SIZE) % SCREEN_SIZE;
        };
    }
};

struct scoring_system {
    bool update(entt::registry& reg) {
        auto snakeHead = reg.view<position_component, spawn_component>().front();
        auto snakeHeadPosition = reg.get<position_component>(snakeHead);

        auto view = reg.view<position_component, static_component>(entt::exclude<direction_component>);
        for (auto entity : view) {
            auto position = view.get<position_component>(entity);
            if(position.x == snakeHeadPosition.x && position.y == snakeHeadPosition.y) {
                reg.destroy(entity);
                return true;
            }
        }
        return false;
    }
};

struct collision_system {
    bool update(entt::registry& reg) {
        auto snakeHead = reg.view<position_component, spawn_component>().front();
        auto snakeHeadPosition = reg.get<position_component>(snakeHead);

        auto view = reg.view<position_component, static_component>();
        for (auto entity : view) {
            auto position = view.get<position_component>(entity);
            if(position.x == snakeHeadPosition.x && position.y == snakeHeadPosition.y) {
                return true;
            }
        }
        return false;
    }
};


struct spawn_system {
    void update(entt::registry& reg, std::shared_ptr<Engine::IResourceManager> resourceManager) {
        auto view = reg.view<position_component, direction_component, spawn_component>();
        for(auto entity : view) {
            auto [position, direction] = view.get<position_component, direction_component>(entity);
            auto bodyPart = reg.create();
            reg.emplace<position_component>(bodyPart, position);
            reg.emplace<direction_component>(bodyPart, direction);
            reg.emplace<static_component>(bodyPart);
	        reg.emplace<sprite_component>(bodyPart, resourceManager->getTexture("snake.png"), 0.0f, 0.0f);
        };
    }
};

struct cleanup_system {
    int mCounter;

    cleanup_system() : mCounter(INITIAL_TAIL) { }

    void update(entt::registry& reg) {
        auto entity = reg.view<position_component, direction_component, cleanup_component>().front();
        auto& counter = reg.get<cleanup_component>(entity);
        if(counter.counter > 0) {
            counter.counter--;
        } else {
            auto [position, direction] = reg.get<position_component, direction_component>(entity);
            
            auto bodyPartsView = reg.view<position_component, direction_component>(entt::exclude<cleanup_component>);
            for(auto bodyPart: bodyPartsView) {
                auto [bpPosition, bpDirection] = bodyPartsView.get<position_component, direction_component>(bodyPart);
                if(bpPosition.x == position.x 
                && bpPosition.y == position.y) {
                    direction.x = bpDirection.x;
                    direction.y = bpDirection.y;
                    reg.destroy(bodyPart);
                    return;
                }
            }
        }
    }
};

struct sprite_system 
{
	int mScreenWidth;
    int mScreenHeight;
	std::shared_ptr<Engine::Sprite> mSprite;

    sprite_system()
        : mSprite(std::make_shared<Engine::Sprite>())
    { }

    void update(entt::registry& reg)
    {
        auto view = reg.view<sprite_component, position_component>();
        for(auto entity : view) {
            auto [sprite, position] = view.get(entity);
            sprite.position.x = static_cast<float>(position.x * mScreenWidth / SCREEN_SIZE);
            sprite.position.y = static_cast<float>(position.y * mScreenHeight / SCREEN_SIZE);
        };
    }

    void render(entt::registry& reg, std::shared_ptr<Engine::IRenderer> renderer)
    {
        auto spriteRenderer = std::static_pointer_cast<Engine::SpriteRenderer>(renderer);

        auto view = reg.view<sprite_component>();
        for(auto entity : view) {
            auto sprite = view.get<sprite_component>(entity);
            mSprite->texture = sprite.texture;
            spriteRenderer->drawSprite(mSprite, sprite.position); 
        };
    }
};

struct movement_system 
{
    void update(entt::registry& reg, std::shared_ptr<Engine::IInputManager> input) {
        auto entity = reg.view<direction_component, input_component>().front();
        auto& direction = reg.get<direction_component>(entity);
        if (direction.x == 0) {
            if (input->isKeyDown(37)) {
                direction.x = -1;
                direction.y = 0;
            }
            if (input->isKeyDown(39)) {
                direction.x = 1;
                direction.y = 0;
            }
        }
        if (direction.y == 0) {
            if (input->isKeyDown(40)) {
                direction.x = 0;
                direction.y = -1;
            }
            if (input->isKeyDown(38)) {
                direction.x = 0;
                direction.y = 1;
            }
        }
    }
};
