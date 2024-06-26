#define _USE_MATH_DEFINES
#include <cmath>

#include "ModelScene.hpp"
#include <vector>
#include "utilities/IOC.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/StepTimer.hpp"
#include "utilities/Config.hpp"
#include "utilities/Logger.hpp"
#include "resources/IResourceManager.hpp"
#include "resources/Shader.hpp"
#include "renderers/ModelRenderer.hpp"
#include "renderers/Camera.hpp"
#include "resources/Model.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "input/IInputManager.hpp"
#include "scenes/ISceneManager.hpp"
#include "SpriteScene.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace Sample;

void ModelScene::load()
{
    debuglog << "[ModelScene::load]" << endl;

    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    resourceManager->loadShader("model", "model.vs", "model.fs");
    resourceManager->loadModel("cube.mdl");
    auto model = resourceManager->getModel("cube.mdl");
    mModels.emplace_back(model);
    angle = 0.0f;

    if (IOCContainer::instance().contains<ModelRenderer>())
    {
        mRenderer = IOCContainer::instance().resolve<ModelRenderer>();
    }
    else
    {
        auto camera = make_shared<Engine::Camera>(glm::vec3(0.0f, 0.0f, 7.0f));
        auto shader = resourceManager->getShader("model");
        mRenderer = make_shared<ModelRenderer>(shader, camera);
        mRenderer->initialize();
        IOCContainer::instance().register_type<ModelRenderer>(mRenderer);
    }

    mInputManager = IOCContainer::instance().resolve<IInputManager>();
    mAnimate = true;
}

void ModelScene::unload()
{
    debuglog << "[ModelScene::unload]" << endl;
    mRenderer.reset();
}

void ModelScene::updateScreenSize(int width, int height)
{
    debuglog << "[ModelScene::updateScreenSize]" << endl;
    mRenderer->updateWindowSize(width, height);
}

void ModelScene::update(shared_ptr<IStepTimer> timer)
{
    auto const mouseState = mInputManager->getMouseState();
    mInputManager->update();
    if (mouseState.state == ButtonState::Pressed)
    {
        auto sceneManager = IOCContainer::instance().resolve<ISceneManager>();
        sceneManager->addScene(make_shared<SpriteScene>());
        sceneManager->removeScene(typeid(ModelScene));
    }

    if (mAnimate)
    {
        angle = timer->getElapsedSeconds();
    }
}

void ModelScene::draw(shared_ptr<IRenderer> renderer)
{
    debuglog << "[ModelScene::draw]" << endl;
    // draw sprites or models
    mRenderer->clear();
    glm::mat4 world = glm::mat4(1.0f);
    world = glm::rotate(world, angle, glm::vec3(1.0f, 1.0, 0.0f));
    for (const auto &model : mModels)
    {
        for (int x = -1; x < 2; x++)
            for (int y = -1; y < 2; y++)
                for (int z = -1; z < 2; z++)
                {
                    auto newWorld = glm::translate(world, glm::vec3(
                                                              static_cast<float>(x),
                                                              static_cast<float>(y),
                                                              static_cast<float>(z)));
                    newWorld = glm::scale(newWorld, glm::vec3(0.75f, 0.75f, 0.75f));
                    mRenderer->drawModel(model, newWorld);
                }
    }
}
