#pragma once

class ScoreSystem
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

private:
    int mLatestScore;
    int mHighScore;
};
