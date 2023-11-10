#pragma once
// thirdparty
#include <memory>
#include <entt/entity/registry.hpp>
#include <random>

// engine
#include "input/IInputManager.hpp"
#include "sprites/Sprite.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/MathHelper.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"

// game
#include "game/Components.hpp"
#include "game/GameDefines.hpp"

struct TransformSystem
{
    void update(entt::registry &reg)
    {
        auto view = reg.view<PositionComponent, DirectionComponent>(entt::exclude<StaticComponent>);
        for (auto entity : view)
        {
            auto [position, direction] = view.get(entity);
            position.x = (position.x + direction.x + SCREEN_SIZE) % SCREEN_SIZE;
            position.y = (position.y + direction.y + SCREEN_SIZE) % SCREEN_SIZE;
        };
    }
};

struct ScoringSystem
{
    bool update(entt::registry &reg)
    {
        auto snakeHead = reg.view<PositionComponent, SpawnComponent>().front();
        auto snakeHeadPosition = reg.get<PositionComponent>(snakeHead);

        auto view = reg.view<PositionComponent, StaticComponent>(entt::exclude<DirectionComponent>);
        for (auto entity : view)
        {
            auto position = view.get<PositionComponent>(entity);
            if (position.x == snakeHeadPosition.x && position.y == snakeHeadPosition.y)
            {
                reg.destroy(entity);
                return true;
            }
        }
        return false;
    }
};

struct CollisionSystem
{
    bool update(entt::registry &reg)
    {
        auto snakeHead = reg.view<PositionComponent, SpawnComponent>().front();
        auto snakeHeadPosition = reg.get<PositionComponent>(snakeHead);

        auto view = reg.view<PositionComponent, StaticComponent>();
        for (auto entity : view)
        {
            auto position = view.get<PositionComponent>(entity);
            if (position.x == snakeHeadPosition.x && position.y == snakeHeadPosition.y)
            {
                return true;
            }
        }
        return false;
    }
};

struct SpawnSystem
{
    std::random_device mRandomDevice;
    std::mt19937 mGen;
    std::uniform_int_distribution<> mDistribution;
    std::shared_ptr<Engine::IResourceManager> mResourceManager;

    SpawnSystem()
        : mGen(mRandomDevice()), mDistribution(0, SCREEN_SIZE - 1), mResourceManager(Utilities::IOCContainer::resolve_type<Engine::IResourceManager>())
    {
    }

    void initialize(entt::registry &reg)
    {
        for (int i = 0; i < NUMBER_OF_APPLES; i++)
        {
            spawnApple(reg);
        }

        auto snakeHead = reg.create();
        reg.emplace<PositionComponent>(snakeHead, 10, 10);
        reg.emplace<DirectionComponent>(snakeHead, 0, 1);
        reg.emplace<SpriteComponent>(snakeHead, mResourceManager->getTexture("snake.png"), 0.0f, 0.0f);
        reg.emplace<InputComponent>(snakeHead);
        reg.emplace<SpawnComponent>(snakeHead);

        auto snakeTail = reg.create();
        reg.emplace<PositionComponent>(snakeTail, 10, 10);
        reg.emplace<DirectionComponent>(snakeTail, 0, 0);
        reg.emplace<CleanupComponent>(snakeTail, INITIAL_TAIL);
    }

    void spawnApple(entt::registry &reg)
    {
        Utilities::Point<int> newPosition{0, 0};
        bool collided;
        do
        {
            collided = false;
            newPosition.x = mDistribution(mGen);
            newPosition.y = mDistribution(mGen);

            auto objects = reg.view<PositionComponent, StaticComponent>();
            for (const auto &object : objects)
            {
                const auto &position = objects.get<PositionComponent>(object);
                if (newPosition.x == position.x && newPosition.y == position.y)
                {
                    collided = true;
                    break;
                }
            }
        } while (collided);

        auto apple = reg.create();
        reg.emplace<PositionComponent>(apple, newPosition.x, newPosition.y);
        reg.emplace<StaticComponent>(apple);
        reg.emplace<SpriteComponent>(apple, mResourceManager->getTexture("apple.png"), 0.0f, 0.0f);
    }

    void update(entt::registry &reg)
    {
        auto view = reg.view<PositionComponent, DirectionComponent, SpawnComponent>();
        for (auto entity : view)
        {
            auto [position, direction] = view.get<PositionComponent, DirectionComponent>(entity);
            auto bodyPart = reg.create();
            reg.emplace<PositionComponent>(bodyPart, position);
            reg.emplace<DirectionComponent>(bodyPart, direction);
            reg.emplace<StaticComponent>(bodyPart);
            reg.emplace<SpriteComponent>(bodyPart, mResourceManager->getTexture("snake.png"), 0.0f, 0.0f);
        };
    }
};

struct CleanupSystem
{
    int mCounter;

    CleanupSystem() : mCounter(INITIAL_TAIL) {}

    void resetCounter(entt::registry &reg, int counter)
    {
        auto entity = reg.view<CleanupComponent>().front();
        reg.replace<CleanupComponent>(entity, counter);
        reg.replace<DirectionComponent>(entity, 0, 0);
    }

    void update(entt::registry &reg)
    {
        auto entity = reg.view<PositionComponent, DirectionComponent, CleanupComponent>().front();
        auto &counter = reg.get<CleanupComponent>(entity);
        if (counter.counter > 0)
        {
            counter.counter--;
        }
        else
        {
            auto [position, direction] = reg.get<PositionComponent, DirectionComponent>(entity);

            auto bodyPartsView = reg.view<PositionComponent, DirectionComponent>(entt::exclude<CleanupComponent>);
            for (auto bodyPart : bodyPartsView)
            {
                auto [bpPosition, bpDirection] = bodyPartsView.get<PositionComponent, DirectionComponent>(bodyPart);
                if (bpPosition.x == position.x && bpPosition.y == position.y)
                {
                    direction.x = bpDirection.x;
                    direction.y = bpDirection.y;
                    reg.destroy(bodyPart);
                    return;
                }
            }
        }
    }
};

struct SpriteSystem
{
    int mScreenWidth;
    int mScreenHeight;
    std::shared_ptr<Engine::Sprite> mSprite;

    SpriteSystem()
        : mSprite(std::make_shared<Engine::Sprite>())
    {
    }

    void updateScreenSize(int width, int height)
    {
        mScreenWidth = width;
        mScreenHeight = height;

        mSprite->size = {
            static_cast<float>(width / SCREEN_SIZE - 1),
            static_cast<float>(height / SCREEN_SIZE - 1)};
    }

    void update(entt::registry &reg)
    {
        auto view = reg.view<SpriteComponent, PositionComponent>();
        for (auto entity : view)
        {
            auto [sprite, position] = view.get(entity);
            sprite.position.x = static_cast<float>(position.x * mScreenWidth / SCREEN_SIZE);
            sprite.position.y = static_cast<float>(position.y * mScreenHeight / SCREEN_SIZE);
        };
    }

    void render(entt::registry &reg, std::shared_ptr<Engine::IRenderer> renderer)
    {
        auto spriteRenderer = std::static_pointer_cast<Engine::SpriteRenderer>(renderer);

        auto view = reg.view<SpriteComponent>();
        for (auto entity : view)
        {
            auto sprite = view.get<SpriteComponent>(entity);
            mSprite->texture = sprite.texture;
            spriteRenderer->drawSprite(mSprite, sprite.position);
        };
    }
};

struct MovementSystem
{
    void update(entt::registry &reg, std::shared_ptr<Engine::IInputManager> input)
    {
        auto entity = reg.view<DirectionComponent, InputComponent>().front();
        auto &direction = reg.get<DirectionComponent>(entity);
        if (direction.x == 0)
        {
            if (input->isKeyDown(37))
            {
                direction.x = -1;
                direction.y = 0;
            }
            if (input->isKeyDown(39))
            {
                direction.x = 1;
                direction.y = 0;
            }
        }
        if (direction.y == 0)
        {
            if (input->isKeyDown(40))
            {
                direction.x = 0;
                direction.y = -1;
            }
            if (input->isKeyDown(38))
            {
                direction.x = 0;
                direction.y = 1;
            }
        }
    }
};
