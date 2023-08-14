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
    
    if(IOCContainer::instance().contains<SpriteRenderer>()) {
        mRenderer = IOCContainer::instance().resolve<SpriteRenderer>();
    } else {
        resourceManager->loadShader( "simple", "simple.vs", "simple.fs" );
        resourceManager->loadTextures({ "tiles.png" });
        
        auto config = IOCContainer::instance().resolve<Utilities::Config>();
        auto camera = make_shared<Engine::OrthographicCamera>( 0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f );
        auto shader = resourceManager->getShader( "simple" );
        mRenderer = make_shared<SpriteRenderer>( shader, camera );
        mRenderer->initialize();
        IOCContainer::instance().register_type<SpriteRenderer>(mRenderer);
    }

    mSprite = make_shared<TiledSprite>();
    mSprite->texture = resourceManager->getTexture( "tiles.png" );
    mSprite->tileSize = { 32, 32 };
    mSprite->size = { 128.0f, 128.0f };
    mSprite->setFrame(1);

    mInputManager = IOCContainer::instance().resolve<IInputManager>();
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
    mSprite->position = { 
        static_cast<float>(width / 2.0f - mSprite->size.width / 2.0f), 
        static_cast<float>(height / 2.0f - mSprite->size.height / 2.0f)
    };
    mRenderer->updateWindowSize( width, height );
}

void SpriteScene::update(shared_ptr<IStepTimer> timer)
{

}

void SpriteScene::draw(shared_ptr<IRenderer> renderer)
{
    mRenderer->clear(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    mRenderer->drawSprite( mSprite );
}
