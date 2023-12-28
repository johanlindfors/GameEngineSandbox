#include "InstructionsScene.hpp"
#include "utilities/IOC.hpp"
#include "scenes/ISceneManager.hpp"
#include "game/IGameStateCallback.hpp"
#include "input/IInputManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "sprites/Sprite.hpp"
#include "utilities/IStepTimer.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

InstructionsScene::InstructionsScene(IGameStateCallback *gameCallback)
	: mInstructions(make_shared<Sprite>())
	, mGetReady(make_shared<Sprite>())
	, mWindowWidth(0)
	, mWindowHeight(0)
	, mGame(gameCallback)
	, mSpacePressedBefore(false)
{
	id = typeid(InstructionsScene).name();

	mInstructions->size = {113.0f, 102.0f};
	mInstructions->position = Point<float>{92, 136};
	mInstructions->offset = {
		382.0f / 512.0f, (512.0f - 104.0f) / 512.0f,
		113.0f / 512.0f, 102.0f / 512.0f}; // 382, 2, 495, 104

	mGetReady->size = {184.0f, 52.0f};
	mGetReady->position = Point<float>{52.0f, 380.0f};
	mGetReady->offset = {
		194.0f / 512.0f, (512.0f - 157.0f) / 512.0f,
		184.0f / 512.0f, 52.0f / 512.0f}; // 194, 105, 378, 157
}

void InstructionsScene::load()
{	
	debuglog << "[InstructionsScene::load]" << endl;

	mInputManager = IOCContainer::instance().resolve<IInputManager>();
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto atlas = resourceManager->getTexture("atlas.png");
	mInstructions->texture.textureIndex = atlas.textureIndex;
	mGetReady->texture.textureIndex = atlas.textureIndex;
}

void InstructionsScene::unload() {}

void InstructionsScene::updateScreenSize(int width, int height)
{
	if (mWindowWidth == width && mWindowHeight == height)
		return;

	mWindowWidth = width;
	mWindowHeight = height;
}

void InstructionsScene::update(shared_ptr<IStepTimer> timer)
{
	auto const spacePressed = mInputManager->isKeyDown(32);
	if (spacePressed && !mSpacePressedBefore)
	{
		mGame->goToState(GameState::GamePlay);
	}
	mSpacePressedBefore = spacePressed;
}

void InstructionsScene::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if (spriteRenderer)
	{
		spriteRenderer->drawSprite(mInstructions);
		spriteRenderer->drawSprite(mGetReady);
	}
}
