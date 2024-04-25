#include "audio/AudioManager.hpp"
#include "utilities/Logger.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"
#include "resources/Sound.hpp"

using namespace std;
using namespace Engine;

void AudioManager::initialize()
{
    mDevice = AlcOpenDevice("");

    if(!mDevice)
    {
        debuglog << "[AudioManager::initialize] Could not open a device!" << endl;
        return;
    }

    mContext = AlcCreateContext(mDevice, NULL);
    if(mContext == NULL || AlcMakeContextCurrent(mContext) == ALC_FALSE)
    {
        if(mContext != NULL)
            AlcDestroyContext(mContext);
        AlcCloseDevice(mDevice);
        debuglog << "[AudioManager::initialize] Could not set a context!" << endl;
        return;
    }

    const ALCchar *name = NULL;
    if(AlcIsExtensionPresent(mDevice, "ALC_ENUMERATE_ALL_EXT"))
        name = AlcGetString(mDevice, ALC_ALL_DEVICES_SPECIFIER);
    if(!name || AlcGetError(mDevice) != AL_NO_ERROR)
        name = AlcGetString(mDevice, ALC_DEVICE_SPECIFIER);

    mResourceManager = Utilities::IOCContainer::resolve_type<IResourceManager>();

    debuglog << "[AudioManager::initialize] Opened: " << name << endl;
}

AudioManager::~AudioManager()
{
    ALCdevice *device;
    ALCcontext *ctx;

    ctx = AlcGetCurrentContext();
    if(ctx == NULL)
        return;

    device = AlcGetContextsDevice(ctx);

    AlcMakeContextCurrent(NULL);
    AlcDestroyContext(ctx);
    AlcCloseDevice(device);

    debuglog << "[AudioManager::~AudioManager] Destroyed" << endl;
}

void AudioManager::playSound(string name)
{
    debuglog << "[AudioManager::playSound] Playing sound '" << name << "'" << endl;
    auto sound = mResourceManager->getSound(name);
    AlSourcePlay(sound.Source);
}
