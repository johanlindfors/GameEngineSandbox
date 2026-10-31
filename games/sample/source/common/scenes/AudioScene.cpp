#include "AudioScene.hpp"
#include "utilities/IOC.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/StepTimer.hpp"
#include "utilities/Config.hpp"
#include "utilities/Logger.hpp"
#include "resources/IResourceManager.hpp"
#include "resources/Sound.hpp"
#include "renderers/Renderer.hpp"
#include "audio/IAudioManager.hpp"
#include "input/IInputManager.hpp"
#include "scenes/ISceneManager.hpp"
#include "SpriteScene.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace Sample;

AudioScene::AudioScene()
    : mResourceManager(IOCContainer::resolve_type<IResourceManager>())
    , mSceneManager(IOCContainer::resolve_type<ISceneManager>())
    , mInputManager(IOCContainer::resolve_type<IInputManager>())
{ 
    id = typeid(AudioScene).name(); 
}

void AudioScene::load()
{
    debuglog << "[AudioScene::load]" << endl;
    
    if(IOCContainer::instance().contains<IRenderer>()) {
        mRenderer = IOCContainer::instance().resolve<IRenderer>();
    } else {
        mRenderer = make_shared<Renderer>();
        mRenderer->initialize();
        IOCContainer::instance().register_type<IRenderer>(mRenderer);
    }

    if(IOCContainer::instance().contains<IAudioManager>()) {
        mAudioManager = IOCContainer::instance().resolve<IAudioManager>();
    } else {
        mAudioManager = IOCContainer::resolve_type<IAudioManager>();
        IOCContainer::instance().register_type<IAudioManager>(mAudioManager);
    }
	
    mResourceManager->loadSounds({"score.wav"});
}

void AudioScene::unload()
{
    debuglog << "[AudioScene::unload]" << endl;
    mRenderer.reset();
}

void AudioScene::update(shared_ptr<IStepTimer> timer)
{
    auto const mouseState = mInputManager->getMouseState();
    mInputManager->update();
    if (mouseState.state == ButtonState::Pressed)
    {
        mAudioManager->playSound("score.wav");
        mSceneManager->addScene(make_shared<SpriteScene>());
        mSceneManager->removeScene(typeid(AudioScene));
    }
}

void AudioScene::draw(shared_ptr<IRenderer> renderer)
{
    // debuglog << "[AudioScene::draw]" << endl;
    mRenderer->clear(0.35f, 0.35f, 0.34f, 1.0f);
}
