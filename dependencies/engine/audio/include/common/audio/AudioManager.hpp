#pragma once
#include "IAudioManager.hpp"
#include <memory>

namespace Engine
{
    class IResourceManager;

    class AudioManager : public IAudioManager
    {
    public:
        AudioManager() = default;
        ~AudioManager();
        void initialize() override;
        void playSound(std::string name) override;
    
    private:
        ALCdevice* mDevice;
        ALCcontext* mContext;
        std::shared_ptr<IResourceManager> mResourceManager;
    };
}