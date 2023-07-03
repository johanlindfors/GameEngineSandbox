#pragma once
#include "scenes/GameScene.hpp"
#include <functional>
#include <queue>

class IGameStateCallback;

class BootScene : public Engine::GameScene
{
public:
    BootScene(IGameStateCallback* gameCallback);
    ~BootScene() = default;
    void load() override;
    void unload() override;
    void updateScreenSize(int width, int height) override;
    void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
    void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

private:
    bool mInitialized;
    IGameStateCallback* mGame;
    std::queue<std::function<void()> > mLoadingTasks;
    uint mLoadedTasks;
    uint mTotalTasks;
};
