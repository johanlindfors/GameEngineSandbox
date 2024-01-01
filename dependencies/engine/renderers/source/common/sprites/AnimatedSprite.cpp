#include "sprites/AnimatedSprite.hpp"

using namespace std;

namespace Engine
{
    void AnimatedSprite::play(string name)
    {
        currentAnimation = name;
        isPlaying = true;
        elapsedMicroSeconds = 0;
        currentFrame = 0;
    }

    void AnimatedSprite::pause()
    {
        isPlaying = false;
    }

    void AnimatedSprite::resume()
    {
        isPlaying = true;
    }

    void AnimatedSprite::reset()
    {
        elapsedMicroSeconds = 0;
        currentFrame = 0;
    }

    void AnimatedSprite::update(shared_ptr<IStepTimer> timer)
    {
        if (isPlaying == false)
            return;

        elapsedMicroSeconds += timer->getDeltaMicroSeconds();

        auto current = &animations[currentAnimation];
        if (elapsedMicroSeconds >= current->frames[currentFrame].durationInMicroSeconds)
        {
            // next frame in animation
            elapsedMicroSeconds -= current->frames[currentFrame].durationInMicroSeconds;
            currentFrame++;
            if (current->loop)
            {
                currentFrame %= current->frames.size();
            }
            else
            {
                if (currentFrame > current->frames.size())
                {
                    isPlaying = false;
                }
            }
            currentTile = current->frames[currentFrame].tile;
            calculateTileOffset();
        }
    }
}