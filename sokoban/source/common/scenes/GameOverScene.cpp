#include "GameOverScene.hpp"

GameOverScene::GameOverScene(IGameStateCallback* gameCallback)
{
    id = typeid(GameOverScene).name();
}

GameOverScene::~GameOverScene()
{}

void GameOverScene::load()
{}

void GameOverScene::unload()
{}

void GameOverScene::updateScreenSize(int width, int height)
{}

void GameOverScene::update(std::shared_ptr<Utilities::IStepTimer> timer)
{}

void GameOverScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{}

void GameOverScene::handleInput()
{}
