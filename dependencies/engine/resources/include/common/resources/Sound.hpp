#pragma once
#include "utilities/ALHelper.hpp"

namespace Engine
{
    struct Sound {
        ALuint Buffer;
        unsigned int Source;
        std::string Name;
        unsigned char Channels;
        int SampleRate;
        unsigned char BitsPerSample;
    };
}
