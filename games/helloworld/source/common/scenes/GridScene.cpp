#include "GridScene.hpp"
#include "utilities/IOC.hpp"
#include "utilities/MathHelper.hpp"
#include "resources/IResourceManager.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utilities/StepTimer.hpp"
#include "resources/Shader.hpp"
#include "sprites/Sprite.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Camera.hpp"
#include "utilities/Config.hpp"
#include "input/IInputManager.hpp"
#include "scenes/ISceneManager.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

void GridScene::load()
{
    printf("[GridScene::load]\n");
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();

    if(IOCContainer::instance().contains<SpriteRenderer>()) {
        mRenderer = IOCContainer::instance().resolve<SpriteRenderer>();
    } else {
        resourceManager->loadTextures({ "grid.png" });
        resourceManager->loadShader( "simple", "simple.vs", "simple.fs" );
        
        auto config = IOCContainer::instance().resolve<Utilities::Config>();
        auto camera = make_shared<Engine::OrthographicCamera>(0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f);
        auto shader = resourceManager->getShader("simple");
        mRenderer = make_shared<SpriteRenderer>(shader, camera);
        mRenderer->initialize();
        IOCContainer::instance().register_type<SpriteRenderer>(mRenderer);
    }

    mSprite = make_shared<Sprite>();
    mSprite->texture = resourceManager->getTexture( "grid.png" );
    mSprite->size = { 51.2f, 51.2f };
    mSprite->position = { 0.0f, 0.0f };

    mInputManager = IOCContainer::instance().resolve<IInputManager>();
}

void GridScene::unload()
{
    printf("[GridScene::unload]\n");
    mRenderer.reset();
    mSprite.reset();
}

void GridScene::updateScreenSize(int width, int height)
{
    printf("[GridScene::updateScreenSize]\n");
    mRenderer->updateWindowSize(width, height);
}

void GridScene::update(shared_ptr<IStepTimer> timer)
{

}

void GridScene::draw(shared_ptr<IRenderer> renderer)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    mRenderer->drawSprite(mSprite);
}
