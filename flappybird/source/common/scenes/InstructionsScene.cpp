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
	, mGetReady(make_shared<Sprite>())
	, mWindowWidth(0)
	, mWindowHeight(0)
	, mGame(gameCallback)
    , mSpacePressedBefore(true)
{
	ID = typeid(InstructionsScene).name();

	mInstructions->Offset = 6;
	mInstructions->Width = 113;
	mInstructions->Height = 102;
	mInstructions->Position = Point<float>(92,136);

	mGetReady->Offset = 8;
	mGetReady->Width = 184;
	mGetReady->Height = 52;
	mGetReady->Position = Point<float>(52,380);
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

void InstructionsScene::Draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	if (spriteRenderer) {
		spriteRenderer->DrawSprite(mInstructions);
		spriteRenderer->DrawSprite(mGetReady);
	}
}
