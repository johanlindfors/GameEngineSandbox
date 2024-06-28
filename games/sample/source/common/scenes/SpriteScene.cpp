#include "SpriteScene.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utilities/IOC.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/StepTimer.hpp"
#include "utilities/Config.hpp"
#include "utilities/Logger.hpp"
#include "resources/IResourceManager.hpp"
#include "resources/Shader.hpp"
#include "sprites/Sprite.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Camera.hpp"
#include "input/IInputManager.hpp"
#include "scenes/ISceneManager.hpp"
#include "ModelScene.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace Sample;

void SpriteScene::load()
{
    debuglog << "[SpriteScene::load]" << endl;
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();

    if(IOCContainer::instance().contains<SpriteRenderer>()) {
        mRenderer = IOCContainer::instance().resolve<SpriteRenderer>();
    } else {
        resourceManager->loadTextures({ "coderox.png" });
        resourceManager->loadShader( "simple", "simple.vs", "simple.fs" );
        
        auto config = IOCContainer::instance().resolve<Utilities::Config>();
        auto camera = make_shared<Engine::OrthographicCamera>(0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f);
        auto shader = resourceManager->getShader("simple");
        mRenderer = make_shared<SpriteRenderer>(shader, camera);
        mRenderer->initialize();
        IOCContainer::instance().register_type<IRenderer>(mRenderer);
    }

    mSprite = make_shared<Sprite>();
    mSprite->texture = resourceManager->getTexture( "coderox.png" );
    mSprite->size = { 256.0f, 256.0f };

    mInputManager = IOCContainer::instance().resolve<IInputManager>();
}

void SpriteScene::unload()
{
    debuglog << "[SpriteScene::unload]" << endl;
    mRenderer.reset();
    mSprite.reset();
}

void SpriteScene::updateScreenSize(int width, int height)
{
    debuglog << "[SpriteScene::updateScreenSize]" << endl;
    mSprite->position = {
        static_cast<float>(width / 2.0f - mSprite->size.width / 2.0f),
        static_cast<float>(height / 2.0f - mSprite->size.height / 2.0f)};
    mRenderer->updateWindowSize(width, height);
}

void SpriteScene::update(shared_ptr<IStepTimer> timer)
{
    auto const mouseState = mInputManager->getMouseState();
    mInputManager->update();
    if (mouseState.state == ButtonState::Pressed)
    {
        auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
        sceneManager->removeScene(typeid(SpriteScene));
        sceneManager->addScene(make_shared<ModelScene>());
    }
}

void SpriteScene::draw(shared_ptr<IRenderer> renderer)
{
    // debuglog << "[SpriteScene::draw]" << endl;
    mRenderer->clear(0.35f, 0.35f, 0.34f, 1.0f);
    GlClear(GL_COLOR_BUFFER_BIT);
    GlDisable(GL_DEPTH_TEST);

    mRenderer->drawSprite(mSprite);
}
