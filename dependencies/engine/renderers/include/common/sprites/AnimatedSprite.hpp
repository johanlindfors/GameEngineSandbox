#pragma once
#include "TiledSprite.hpp"
#include <vector>

namespace Engine
{
    struct AnimationFrame
    {
        unsigned int tile;
        unsigned int durationInMicroSeconds;
    };

    struct Animation
    {
        std::vector<AnimationFrame> frames;
        bool loop;
    };

    struct AnimatedSprite : public TiledSprite
    {
        std::map<std::string, Animation> animations;
        std::string currentAnimation;
        bool isPlaying;
        unsigned int currentFrame;
        unsigned int elapsedMicroSeconds;

        void play(std::string name);
        void pause();
        void resume();
        void reset();
        void update(std::shared_ptr<Engine::IStepTimer> timer);
    };
}
