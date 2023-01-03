#include "GameStateMachine.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "scenes/GenericScene.h"

using namespace std;
using namespace Utilities;
using namespace Engine;
using namespace Sample;

void GameStateMachine::Initialize()
{
	auto sceneManager = IOCContainer::Instance().Resolve<ISceneManager>();
	sceneManager->AddScene(make_shared<GenericScene>());
}
