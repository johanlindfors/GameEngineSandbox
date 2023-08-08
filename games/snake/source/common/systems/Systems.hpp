#pragma once
#include <memory>
#include <entt/entity/registry.hpp>
#include "sprites/Sprite.hpp"
#include "components/Components.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "game/GameDefines.hpp"
#include "resources/IResourceManager.hpp"

struct transform_system {
    void update(entt::registry& reg) {
        auto view = reg.view<position_component, direction_component>(entt::exclude<static_component>);
        view.each([](auto &p, auto& d) { 
            p.x = (p.x + d.x + SCREEN_SIZE) % SCREEN_SIZE;
            p.y = (p.y + d.y + SCREEN_SIZE) % SCREEN_SIZE;
        });
    }
};

struct scoring_system {
    bool update(entt::registry& reg) {
        auto snakeHead = reg.view<position_component, spawn_component>().front();
        auto snakeHeadPosition = reg.get<position_component>(snakeHead);

        auto apples = reg.view<position_component, static_component>(entt::exclude<direction_component>);
        for (const auto apple : apples)
        {
            auto applePosition = apples.get<position_component>(apple);
            if(applePosition.x == snakeHeadPosition.x && applePosition.y == snakeHeadPosition.y) {
                reg.destroy(apple);
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

        auto body = reg.view<position_component, static_component>();
        for (const auto bodyPart : body) {
            auto position = body.get<position_component>(bodyPart);
            if(position.x == snakeHeadPosition.x && position.y == snakeHeadPosition.y) {
                return true;
            }
        }
        return false;
    }
};


struct spawn_system {
    void update(entt::registry& reg, std::shared_ptr<Engine::IResourceManager> resourceManager)
    {
        auto view = reg.view<position_component, direction_component, spawn_component>();
        view.each([&reg, &resourceManager](auto& p, auto& d) {
            auto bodyPart = reg.create();
            reg.emplace<position_component>(bodyPart, p.x, p.y);
            reg.emplace<direction_component>(bodyPart, d.x, d.y);
            reg.emplace<static_component>(bodyPart);
	        reg.emplace<sprite_component>(bodyPart, resourceManager->getTexture("snake.png"), 0.0f, 0.0f);
        });
    }
};

struct cleanup_system {
    void update(entt::registry& reg) {
        auto view = reg.view<position_component, direction_component, cleanup_component>();
        for(auto entity: view) {
            auto &cleanup = view.get<cleanup_component>(entity);
            if(cleanup.counter > 0) {
                cleanup.counter--;
            } else {
                auto& position = view.get<position_component>(entity);
                auto& direction = view.get<direction_component>(entity);
                
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
    }
};

struct sprite_system 
{
	int mScreenWidth;
	std::shared_ptr<Engine::Sprite> mSprite;

    void update(entt::registry& reg)
    {
        auto view = reg.view<sprite_component, position_component>();
        view.each([&](auto &s, auto &p){
            s.position.x = static_cast<float>(p.x * mScreenWidth / SCREEN_SIZE);
            s.position.y = static_cast<float>(p.y * mScreenWidth / SCREEN_SIZE);
        });
    }

    void render(entt::registry& reg, std::shared_ptr<Engine::IRenderer> renderer)
    {
        auto spriteRenderer = std::static_pointer_cast<Engine::SpriteRenderer>(renderer);

        auto view = reg.view<sprite_component>();
        view.each([&, spriteRenderer](auto &s){
            mSprite->texture = s.texture;
            spriteRenderer->drawSprite(mSprite, s.position); 
        });
    }
};

struct movement_system 
{
    void update(entt::registry& reg, std::shared_ptr<Engine::IInputManager> input) {
        auto view = reg.view<direction_component, input_component>();
        view.each([&input](auto &d){
            if (d.x == 0) {
                if (input->isKeyDown(37)) {
                    d.x = -1;
                    d.y = 0;
                }
                if (input->isKeyDown(39)) {
                    d.x = 1;
                    d.y = 0;
                }
            }
            if (d.y == 0) {
                if (input->isKeyDown(40)) {
                    d.x = 0;
                    d.y = -1;
                }
                if (input->isKeyDown(38)) {
                    d.x = 0;
                    d.y = 1;
                }
            }
        });
    }
};
