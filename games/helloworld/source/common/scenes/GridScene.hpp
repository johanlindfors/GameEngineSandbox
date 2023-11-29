#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.hpp"

class IGameStateCallback;
namespace Engine
{
    class SpriteRenderer;
    class IInputManager;
    struct Sprite;
}

namespace Utilities
{
    class IStepTimer;
}

class GridScene : public Engine::GameScene
{
public:
    GridScene() { id = typeid(GridScene).name(); }

    // Engine::GameScene
    void load() override;
    void unload() override;
    void updateScreenSize(int width, int height) override;
    void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
    void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
    std::shared_ptr<Engine::SpriteRenderer> mRenderer;
    std::shared_ptr<Engine::Sprite> mSprite;
    std::shared_ptr<Engine::IInputManager> mInputManager;
};
