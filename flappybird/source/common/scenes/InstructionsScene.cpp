#include "InstructionsScene.h"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.h"
#include "game/IGameStateCallback.h"
#include "input/IInputManager.h"
#include "renderers/ISpriteRenderer.h"
#include "renderers/Sprite.h"
#include "utilities/IStepTimer.h"


using namespace std;
using namespace Engine;
using namespace Utilities;

InstructionsScene::InstructionsScene(IGameStateCallback* gameCallback)
	: mInstructions(make_shared<Sprite>())
	, mWindowWidth(0)
	, mWindowHeight(0)
	, mGame(gameCallback)
    , mSpacePressedBefore(true)
{
	ID = typeid(InstructionsScene).name();

	mInstructions->Offset = 6;
	mInstructions->Width = 113;
	mInstructions->Height = 102;
	mInstructions->Position = Point<float>(92,176);
}

InstructionsScene::~InstructionsScene()
{

}

void InstructionsScene::Load()
{
	mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
}

void InstructionsScene::Unload() { }

void InstructionsScene::UpdateScreenSize(int width, int height) 
{
	if(mWindowWidth == width && mWindowHeight == height)
		return;

	mWindowWidth = width;
	mWindowHeight = height;
}

void InstructionsScene::Update(shared_ptr<IStepTimer> timer)
{	
	auto const spacePressed = mInputManager->IsKeyDown(32);
    if (spacePressed && !mSpacePressedBefore) {
        mGame->GoToState(GameState::GamePlay);
    }
	mSpacePressedBefore = spacePressed;
}

void InstructionsScene::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	if (renderer) {
		renderer->DrawSprite(mInstructions);
	}
}
