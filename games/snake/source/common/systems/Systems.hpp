#pragma once
#include <memory>
#include <entt/entity/registry.hpp>
#include "sprites/Sprite.hpp"
#include "components/Components.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "game/GameDefines.hpp"

struct transform_system {
    void update(entt::registry& reg) {
        auto view = reg.view<position_component, direction_component>();
        view.each([](auto &p, auto& d) { 
            p.x = (p.x + d.x + SCREEN_SIZE) % SCREEN_SIZE;
            p.y = (p.y + d.y + SCREEN_SIZE) % SCREEN_SIZE;
        });
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
