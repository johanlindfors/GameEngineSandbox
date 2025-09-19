#include "SpriteScene.hpp"
#include "utilities/IOC.hpp"
#include "utilities/MathHelper.hpp"
#include "resources/IResourceManager.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utilities/StepTimer.hpp"
#include "resources/Shader.hpp"
#include "sprites/TiledSprite.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Camera.hpp"
#include "utilities/Config.hpp"
#include "input/IInputManager.hpp"
#include "scenes/ISceneManager.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace Sample;

void SpriteScene::load()
{
    debuglog << "[SpriteScene::load]" << std::endl;
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();

    resourceManager->loadShader("simple", "simple.vs", "simple.fs");
    resourceManager->loadTextures({"tiles_sample.png"});
    mSpriteSystem->setTexture(resourceManager->getTexture("tiles_sample.png"));

    auto config = IOCContainer::instance().resolve<Utilities::Config>();
    mCamera = make_shared<Engine::OrthographicCamera>(0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f);
    auto shader = resourceManager->getShader("simple");
    mRenderer = make_shared<SpriteRenderer>(shader, mCamera);
    mRenderer->initialize();

    IOCContainer::instance().register_type<IRenderer>(mRenderer);

    mInputManager = IOCContainer::instance().resolve<IInputManager>();

    placeTile(0, 0, 25, 0);
}

void SpriteScene::placeTile(int x, int y, int frame, int zOrder)
{
    auto offset = mSpriteSystem->getViewOffset();
    int xPos = x - offset.x;
    int yPos = y - offset.y;
    xPos = (int)((xPos + TILE_WIDTH / (xPos >= 0 ? 2 : -2)) / TILE_WIDTH);
    yPos = (int)((yPos + TILE_HEIGHT / (yPos >= 0 ? 2 : -2)) / TILE_HEIGHT);

    bool tileExists = false;
    auto view = mRegistry.view<SpriteComponent, PositionComponent>();
    for (auto entity : view)
    {
        auto [sprite, position] = view.get(entity);
        if (position.x == xPos && position.y == yPos)
        {
            tileExists = true;
            mRegistry.replace<SpriteComponent>(entity, frame, zOrder);
            break;
        }
    };
    if (!tileExists)
    {
        auto tile = mRegistry.create();
        mRegistry.emplace<PositionComponent>(tile, xPos, yPos);
        mRegistry.emplace<DirectionComponent>(tile, (Direction)(rand() % 4));
        mRegistry.emplace<SpriteComponent>(tile, frame, zOrder);
    }
    auto spriteView = mRegistry.view<SpriteComponent>();
    debuglog << "[SpriteScene::placeTile] Number of tiles: " << spriteView.size() << std::endl;
}

void SpriteScene::unload()
{
    debuglog << "[SpriteScene::unload]" << std::endl;
    mRenderer.reset();
}

void SpriteScene::updateScreenSize(int width, int height)
{
    debuglog << "[SpriteScene::updateScreenSize]" << std::endl;
    mCamera->right = width;
    mCamera->top = height;

    mSpriteSystem->updateScreenSize(width, height);
}

void SpriteScene::update(shared_ptr<IStepTimer> timer)
{
    auto const mouseState = mInputManager->getMouseState();
    auto translatedCoordinate = mCamera->translateScreenToGameCoordinate(
        mouseState.position.x,
        mouseState.position.y);
    switch (mouseState.state)
    {
    case ButtonState::Pressed:
        placeTile(
            translatedCoordinate.x,
            translatedCoordinate.y,
            rand() % 24, 1);
        mMouseDownX = mouseState.position.x;
        mMouseDownY = mouseState.position.y;
        break;
    case ButtonState::Repeat:
        mSpriteSystem->setMouseMoveOffset(
            mMouseDownX != 0 ? mouseState.position.x - mMouseDownX : mMouseDownX,
            mMouseDownY != 0 ? mouseState.position.y - mMouseDownY : mMouseDownY);
        mMouseDownX = mouseState.position.x;
        mMouseDownY = mouseState.position.y;
        break;

    default:
        mMouseDownX = 0;
        mMouseDownY = 0;
        break;
    }
}

void SpriteScene::draw(shared_ptr<IRenderer> renderer)
{
    mRenderer->clear(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    mSpriteSystem->render(mRegistry, mRenderer);
}
