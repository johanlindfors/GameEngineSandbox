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
	id = typeid(InstructionsScene).name();

	mInstructions->offset = 6;
	mInstructions->width = 113;
	mInstructions->height = 102;
	mInstructions->position = Point<float>{92,136};

	mGetReady->offset = 8;
	mGetReady->width = 184;
	mGetReady->height = 52;
	mGetReady->position = Point<float>{52,380};
}

void InstructionsScene::load()
{
	mInputManager = IOCContainer::instance().resolve<IInputManager>();
}

void InstructionsScene::unload() { }

void InstructionsScene::updateScreenSize(int width, int height) 
{
	if(mWindowWidth == width && mWindowHeight == height)
		return;

	mWindowWidth = width;
	mWindowHeight = height;
}

void InstructionsScene::update(shared_ptr<IStepTimer> timer)
{	
	auto const spacePressed = mInputManager->isKeyDown(32);
    if (spacePressed && !mSpacePressedBefore) {
        mGame->goToState(GameState::GamePlay);
    }
	mSpacePressedBefore = spacePressed;
}

void InstructionsScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<ISpriteRenderer>(renderer);
	if (spriteRenderer) {
		spriteRenderer->drawSprite(mInstructions);
		spriteRenderer->drawSprite(mGetReady);
	}
}
