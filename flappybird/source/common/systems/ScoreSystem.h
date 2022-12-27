#pragma once
#include "utilities/ILazyInitialized.h"

class ScoreSystem : public Utilities::ILazyInitialized 
{
    public:
        ScoreSystem() 
            : mLatestScore(0)
            , mHighScore(0) { }
        ~ScoreSystem() = default;
        int GetLatestScore() { return mLatestScore; }
        int GetHighScore() { return mHighScore; }
        void SetLatestScore(int score);
        void SaveHighScore();
        void LoadHighScore();

        // Utilities::ILazyInitialized
        void LazyInitialize();

    private:
        int mLatestScore;
        int mHighScore;
};
