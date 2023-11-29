#include "Game.hpp"
#include <memory>
#include "utilities/GLHelper.hpp"
#include "GameDefines.hpp"
#include "scenes/GridScene.hpp"
#include "scenes/ISceneManager.hpp"
#include "utilities/IOC.hpp"

void Game::initialize()
{
    Engine::GlClearColor(CORNFLOWER_BLUE);
	auto sceneManager = Utilities::IOCContainer::instance().resolve<Engine::ISceneManager>();
	sceneManager->addScene(std::make_shared<GridScene>());
}
