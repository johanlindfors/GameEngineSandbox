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
    
    resourceManager->loadShader( "simple", "simple.vs", "simple.fs" );
    resourceManager->loadTextures({ "tiles.png" });
    mSpriteSystem->setTexture(resourceManager->getTexture("tiles.png"));
    auto config = IOCContainer::instance().resolve<Utilities::Config>();
    mCamera = make_shared<Engine::OrthographicCamera>( 0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f );
    auto shader = resourceManager->getShader( "simple" );
    mRenderer = make_shared<SpriteRenderer>( shader, mCamera );
    mRenderer->initialize();

    IOCContainer::instance().register_type<IRenderer>(mRenderer);

    mInputManager = IOCContainer::instance().resolve<IInputManager>();

    placeTile(0,0,1);
}

void SpriteScene::placeTile(int x, int y, int frame)
{
    auto tile = mRegistry.create();
    auto offset = mSpriteSystem->getViewOffset();
    int xPos = x - offset.x;
    int yPos = y - offset.y;
    if(xPos >= 0) xPos = (int)((xPos + TILE_WIDTH / 2) / TILE_WIDTH) * TILE_WIDTH;
    else xPos = (int)((xPos - TILE_WIDTH / 2) / TILE_WIDTH) * TILE_WIDTH;
    if(yPos >= 0) yPos = (int)((yPos + TILE_HEIGHT / 2) / TILE_HEIGHT) * TILE_HEIGHT;
    else yPos = (int)((yPos - TILE_HEIGHT / 2) / TILE_HEIGHT) * TILE_HEIGHT;
    mRegistry.emplace<PositionComponent>(tile, xPos, yPos);
    mRegistry.emplace<DirectionComponent>(tile, Direction::North);
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    mRegistry.emplace<SpriteComponent>(tile, frame, 0.0f, 0.0f);
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
        mouseState.position.y
    );
    // if(mouseState.state != ButtonState::None)
    //     debuglog << "TX: " << translatedCoordinate.x << " TY: " << translatedCoordinate.y << endl;
    switch (mouseState.state) {
        case ButtonState::Pressed:
        placeTile(
            translatedCoordinate.x, 
            translatedCoordinate.y,
            1
        );
        mMouseDownX = mouseState.position.x;
        mMouseDownY = mouseState.position.y;    
        //debuglog << "TX: " << mouseState.position.x << " TY: " << mouseState.position.y << endl;
        break;
        case ButtonState::Repeat:
        mSpriteSystem->setMouseMoveOffset(
            mMouseDownX != 0 ? mouseState.position.x - mMouseDownX : mMouseDownX,
            mMouseDownY != 0 ? mouseState.position.y - mMouseDownY : mMouseDownY
        );
        mMouseDownX = mouseState.position.x;
        mMouseDownY = mouseState.position.y;    
        break;

        default:
        mMouseDownX = 0;
        mMouseDownY = 0;
        break;
    }

    mSpriteSystem->update(mRegistry);
}

void SpriteScene::draw(shared_ptr<IRenderer> renderer)
{
    mRenderer->clear(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    mSpriteSystem->render(mRegistry, mRenderer);
}
