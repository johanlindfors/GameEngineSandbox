#pragma once
#include "MathHelper.hpp"

namespace Utilities {
    class ScreenToGameCoordinatesConverter 
    {
        public:
            ScreenToGameCoordinatesConverter() {}
            void setGameSize(Size<int> gameSize) { mGameSize = gameSize; }
            void setScreenSize(Size<int> screenSize) { mScreenSize = screenSize; }
            Size<float> getAspects() { 
                return {
                    static_cast<float>(mGameSize.width) / static_cast<float>(mScreenSize.width), 
                    static_cast<float>(mGameSize.height) / static_cast<float>(mScreenSize.height)};
            }
            Size<int> getGameSize() { return mGameSize; }
        
        private:
            Size<int> mGameSize;
            Size<int> mScreenSize;
    };
}