#include "BootScene.hpp"
#include "game/IGameStateCallback.hpp"

BootScene::BootScene(IGameStateCallback* gameCallback)
{
    id = typeid(BootScene).name();
    mGame = gameCallback;
}

void BootScene::load()
{}

void BootScene::unload()
{}

void BootScene::updateScreenSize(int width, int height)
{}

void BootScene::update(std::shared_ptr<Utilities::IStepTimer> timer)
{
    mGame->goToState(GameState::GamePlay);
}

void BootScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{}