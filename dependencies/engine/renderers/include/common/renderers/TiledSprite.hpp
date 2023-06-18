#pragma once
#include "Sprite.hpp"
#include <string>
#include <map>
#include "utilities/IStepTimer.hpp"

namespace Engine 
{
	struct TiledSprite : public Sprite 
    {
		Utilities::Size<int> tileSize;
		unsigned int currentTile;

		unsigned int getCols() {
			return texture.width / tileSize.width;
		}

		unsigned int getRows() {
			return texture.height / tileSize.height;
		}

		Utilities::Rectangle<float> calculateTileOffset() {
			Utilities::Size<float> normalizedTileSize = {
				static_cast<float>(tileSize.width) / texture.width,
				static_cast<float>(tileSize.height) / texture.height
			};
			offset = {
				static_cast<float>(currentTile % getCols() * normalizedTileSize.width),
				1.0f - static_cast<float>(static_cast<int>(currentTile / getCols() + 1) * normalizedTileSize.height),
				normalizedTileSize.width,
				normalizedTileSize.height
			};
			return offset;
		}
	};

    struct AnimationFrame {
        unsigned int tile;
        unsigned int durationInMicroSeconds;
    };

    struct Animation {
        std::string name;
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
