#pragma once
#include "utilities/alwrapper.hpp"
#include <string>

namespace Engine
{
    // Wrapping al*

    ALCdevice* AlcOpenDevice(std::string name);
    ALCcontext* AlcCreateContext(ALCdevice *device, const ALCint *attrlist);
    bool AlcMakeContextCurrent(ALCcontext *context);
    void AlcDestroyContext(ALCcontext *context);
    bool AlcIsExtensionPresent(ALCdevice *device, std::string extname);
    const ALCchar* ALC_APIENTRY AlcGetString(ALCdevice *device, ALCenum param);
    ALCenum ALC_APIENTRY AlcGetError(ALCdevice *device);
    ALCcontext* AlcGetCurrentContext();
    ALCdevice* AlcGetContextsDevice(ALCcontext *context);
    
    void AlGenBuffers(ALsizei n, ALuint *buffers);
    void AlBufferData(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);

    void AlGenSources(ALsizei n, ALuint *sources);
    void AlSourcei(ALuint source, ALenum param, ALint value);
    
    void AlGetSourcef(ALuint source, ALenum param, ALfloat *value);
    void AlGetSourcei(ALuint source,  ALenum param, ALint *value);

    void AlDeleteSources(ALsizei n, const ALuint *sources);
    void AlDeleteBuffers(ALsizei n, const ALuint *buffers);

    bool AlcCloseDevice(ALCdevice* device);

    void AlSourcePlay(ALuint source);
}