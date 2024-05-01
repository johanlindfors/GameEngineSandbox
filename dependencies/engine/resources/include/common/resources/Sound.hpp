#pragma once
#include <string>

namespace Engine
{
    struct Sound {
        std::string Name;
        unsigned int Buffer;
        unsigned int Source;
        unsigned char Channels;
        unsigned int SampleRate;
        unsigned char BitsPerSample;
    };
}
