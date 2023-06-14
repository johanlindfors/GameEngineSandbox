#include "GameOverScene.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameOverScene::GameOverScene(IGameStateCallback* gameCallback)
{
    id = typeid(GameOverScene).name();
}

void GameOverScene::load()
{

}

void GameOverScene::unload()
{

}

void GameOverScene::updateScreenSize(int width, int height)
{

}

void GameOverScene::update(shared_ptr<IStepTimer> timer)
{

}

void GameOverScene::draw(shared_ptr<IRenderer> renderer)
{

}

void GameOverScene::handleInput()
{

}
