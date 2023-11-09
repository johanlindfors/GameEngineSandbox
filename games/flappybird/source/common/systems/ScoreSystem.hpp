#pragma once
#include "utilities/ILazyInitialized.hpp"

class ScoreSystem : public Utilities::ILazyInitialized
{
public:
    ScoreSystem()
        : mLatestScore(0), mHighScore(0) {}
    ~ScoreSystem() = default;
    int getLatestScore() { return mLatestScore; }
    int getHighScore() { return mHighScore; }
    void setLatestScore(int score);
    void saveHighScore();
    void loadHighScore();

    // Utilities::ILazyInitialized
    void lazyInitialize();

private:
    int mLatestScore;
    int mHighScore;
};
