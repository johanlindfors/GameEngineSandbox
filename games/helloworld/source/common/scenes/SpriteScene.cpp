#include "SpriteScene.hpp"

// Engine
#include "utilities/IOC.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/StepTimer.hpp"
#include "utilities/Config.hpp"
#include "utilities/Logger.hpp"
#include "resources/IResourceManager.hpp"
#include "resources/Shader.hpp"
#include "sprites/TiledSprite.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Camera.hpp"

// Thirdparty
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Game
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace HelloWorld::Scenes;

void SpriteScene::load()
{
    debuglog << "[SpriteScene::load]" << endl;
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();

    resourceManager->loadTextures({ "grid.png" });
    resourceManager->loadShader( "simple", "simple.vs", "simple.fs" );
    
    auto config = IOCContainer::instance().resolve<Utilities::Config>();
    auto camera = make_shared<Engine::OrthographicCamera>(0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f);
    auto shader = resourceManager->getShader("simple");
    auto renderer = make_shared<SpriteRenderer>(shader, camera);
    renderer->initialize();
    IOCContainer::instance().register_type<IRenderer>(renderer);

    mSprite = make_shared<TiledSprite>();
    mSprite->texture = resourceManager->getTexture( "grid.png" );
    mSprite->tileSize = { 32, 32 };
    mSprite->size = { 256.0f, 256.0f };
    mSprite->setFrame(11);
    mSprite->position = {
        static_cast<float>(config->width / 2.0f - mSprite->size.width / 2.0f),
        static_cast<float>(config->height / 2.0f - mSprite->size.height / 2.0f)};
}

void SpriteScene::unload()
{
    debuglog << "[SpriteScene::unload]" << endl;
    mSprite.reset();
}

void SpriteScene::updateScreenSize(int width, int height)
{
    debuglog << "[SpriteScene::updateScreenSize] Width: " << width << " Height: " << height << endl;
    // mSprite->position = {
    //     static_cast<float>(width / 2.0f - mSprite->size.width / 2.0f),
    //     static_cast<float>(height / 2.0f - mSprite->size.height / 2.0f)};
}

void SpriteScene::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	spriteRenderer->clear(CORNFLOWER_BLUE);
    spriteRenderer->drawSprite(mSprite);
}
