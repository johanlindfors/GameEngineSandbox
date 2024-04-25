#pragma once
#include "utilities/ALHelper.hpp"

namespace Engine
{
    class IAudioManager
    {
    public:
        virtual void initialize() = 0;
        virtual void playSound(std::string name) = 0;
    };
}
