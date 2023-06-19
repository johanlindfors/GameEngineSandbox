#pragma once
#include "TiledSprite.hpp"

namespace Engine
{
    struct AnimationFrame
    {
        unsigned int tile;
        unsigned int durationInMicroSeconds;
    };

    struct Animation
    {
        std::array<AnimationFrame,16> frames;
        unsigned int numberOfFrames;
        bool loop;
    };

    struct AnimatedSprite : public TiledSprite 
    {
        std::map<std::string, Animation> animations;
        std::string currentAnimation;
        bool isPlaying;
        unsigned int currentFrame;
        unsigned int elapsedMicroSeconds;

        void play(std::string name) {
            currentAnimation = name;
            isPlaying = true;
        }
        void pause() { isPlaying = false; }
        void resume() { isPlaying = true; }
        void reset() {
            elapsedMicroSeconds = 0; 
            currentFrame = 0;
        }

        void update(std::shared_ptr<Utilities::IStepTimer> timer) {
            if(isPlaying == false)
                return;

            auto delta = timer->getDeltaMicroSeconds();
            elapsedMicroSeconds += delta;
            auto current = animations[currentAnimation];
            if(elapsedMicroSeconds >= current.frames[currentFrame].durationInMicroSeconds) {
                // next frame in animation
                elapsedMicroSeconds -= current.frames[currentFrame].durationInMicroSeconds;
                currentFrame++;
                if(current.loop) {
                    currentFrame %= current.numberOfFrames;
                } else {
                    if(currentFrame > current.numberOfFrames) {
                        isPlaying = false;
                    }
                }
                animations[currentAnimation] = current;
                currentTile = current.frames[currentFrame].tile;
                printf("[CurrentTile] %u\n", currentTile);
                calculateTileOffset();
            }
        }
    };
}
