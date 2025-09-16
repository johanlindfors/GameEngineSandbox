#include "utilities/ALHelper.hpp"
#include "utilities/Logger.hpp"

using namespace std;

namespace Engine
{
    ALCdevice* AlcOpenDevice(std::string name) {
        debuglog << "[ALHelper::AlcOpenDevice]" << std::endl;
        return alcOpenDevice(name.empty() ? NULL : name.c_str());
    }

    ALCcontext* AlcCreateContext(ALCdevice *device, const ALCint *attrlist) {
        debuglog << "[ALHelper::AlcCreateContext]" << std::endl;
        return alcCreateContext(device, attrlist);
    }

    bool AlcMakeContextCurrent(ALCcontext *context) {
        debuglog << "[ALHelper::AlcMakeContextCurrent]" << std::endl;
        return alcMakeContextCurrent(context);
    }

    void AlcDestroyContext(ALCcontext *context) {
        debuglog << "[ALHelper::AlcDestroyContext]" << std::endl;
        alcDestroyContext(context);
    }

    bool AlcIsExtensionPresent(ALCdevice *device, string extname) {
        debuglog << "[ALHelper::AlcIsExtensionPresent]" << std::endl;
        return alcIsExtensionPresent(device, extname.c_str());
    }
    
    const ALCchar* AlcGetString(ALCdevice *device, ALCenum param){
        debuglog << "[ALHelper::AlcGetString]" << std::endl;
        return alcGetString(device, param);    
    }

    ALCcontext* AlcGetCurrentContext() {
        debuglog << "[ALHelper::AlcGetCurrentContext]" << std::endl;
        return alcGetCurrentContext(); 
    }

    ALCdevice* AlcGetContextsDevice(ALCcontext *context) {
        debuglog << "[ALHelper::AlcGetContextsDevice]" << std::endl;
        return alcGetContextsDevice(context);
    }

    ALCenum AlcGetError(ALCdevice *device) {
        debuglog << "[ALHelper::AlcGetError]" << std::endl;
        return alcGetError(device);
    }

    bool AlcCloseDevice(ALCdevice* device) {
        debuglog << "[ALHelper::AlcCloseDevice]" << std::endl;
        return alcCloseDevice(device);
    }

    void AlGenBuffers(ALsizei n, ALuint *buffers) {
        debuglog << "[ALHelper::AlGenBuffers]" << std::endl;
        alGenBuffers(n, buffers);
    }

    void AlBufferData(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq) {
        debuglog << "[ALHelper::AlBufferData]" << std::endl;
        alBufferData(buffer, format, data, size, freq);
    }

    void AlGenSources(ALsizei n, ALuint *sources) {
        debuglog << "[ALHelper::AlGenSources]" << std::endl;
        alGenSources(n, sources);
    }

    void AlSourcei(ALuint source, ALenum param, ALint value) {
        debuglog << "[ALHelper::AlSourcei]" << std::endl;
        alSourcei(source, param, value);
    }

    void AlGetSourcef(ALuint source, ALenum param, ALfloat *value) {
        debuglog << "[ALHelper::AlGetSourcef]" << std::endl;
        alGetSourcef(source, param, value);
    }

    void AlGetSourcei(ALuint source, ALenum param, ALint *value) {
        debuglog << "[ALHelper::AlGetSourcei]" << std::endl;
        alGetSourcei(source, param, value);
    }

    void AlSourcePlay(ALuint source) {
        debuglog << "[ALHelper::AlSourcePlay]" << std::endl;
        alSourcePlay(source);
    }

    void AlDeleteSources(ALsizei n, const ALuint *sources) {
        debuglog << "[ALHelper::AlDeleteSources]" << std::endl;
        alDeleteSources(n, sources);
    }

    void AlDeleteBuffers(ALsizei n, const ALuint *buffers) {
        debuglog << "[ALHelper::AlDeleteBuffers]" << std::endl;
        alDeleteBuffers(n, buffers);
    }
}