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

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace Sample;

void SpriteScene::load() 
{
    printf("[SpriteScene::load]\n");
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    
    resourceManager->loadShader( "simple", "simple.vs", "simple.fs" );
    resourceManager->loadTextures({ "tiles.png" });
    
    auto config = IOCContainer::instance().resolve<Utilities::Config>();
    auto camera = make_shared<Engine::OrthographicCamera>( 0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f );
    auto shader = resourceManager->getShader( "simple" );
    mRenderer = make_shared<SpriteRenderer>( shader, camera );
    mRenderer->initialize();

    // mSprite = make_shared<TiledSprite>();
    // mSprite->texture = resourceManager->getTexture( "tiles.png" );
    // mSprite->tileSize = { 32, 32 };
    // mSprite->size = { 128.0f, 128.0f };
    // mSprite->setFrame(1);

    // mInputManager = IOCContainer::instance().resolve<IInputManager>();

    auto tile = mRegistry.create();
    mRegistry.emplace<PositionComponent>(tile, 0, 0);
    mRegistry.emplace<DirectionComponent>(tile, Direction::North);
    mRegistry.emplace<SpriteComponent>(tile, resourceManager->getTexture("tiles.png"), 1, 0.0f, 0.0f);
    
    auto anotherTile = mRegistry.create();
    mRegistry.emplace<PositionComponent>(anotherTile, 0, 0);
    mRegistry.emplace<DirectionComponent>(anotherTile, Direction::North);
    mRegistry.emplace<SpriteComponent>(anotherTile, resourceManager->getTexture("tiles.png"), 3, 0.0f, 0.0f);
}

void SpriteScene::unload() 
{
    printf("[SpriteScene::unload]\n");
    mRenderer.reset();
    mSprite.reset();
}

void SpriteScene::updateScreenSize(int width, int height)
{ 
    printf("[SpriteScene::updateScreenSize]\n");
    mSpriteSystem->updateScreenSize(width, height);
}

void SpriteScene::update(shared_ptr<IStepTimer> timer)
{
    mSpriteSystem->update(mRegistry);
}

void SpriteScene::draw(shared_ptr<IRenderer> renderer)
{
    mRenderer->clear(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    mSpriteSystem->render(mRegistry, mRenderer);
}
