#include "ScoreSystem.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"
#include "filesystem/IFileSystem.hpp"
#include "filesystem/File.hpp"
#include <stdio.h>

using namespace std;
using namespace Engine;
using namespace Utilities;

void ScoreSystem::setLatestScore(int score)
{
    mLatestScore = score;
    if (mLatestScore > mHighScore)
    {
        mHighScore = mLatestScore;
        saveHighScore();
        debuglog << "[ScoreSystem::SetLatestScore] HighScore saved: " << mHighScore << endl;
    }
};

void ScoreSystem::loadHighScore()
{
    auto fileSystem = IOCContainer::instance().resolve<IFileSystem>();
    auto saveFile = fileSystem->loadFile("highscore.txt", false);
    int score = 0;
    if (saveFile->isOpen())
    {
        auto fileHandle = saveFile->get();
        fscanf(fileHandle, "%d", &score);
    }
    saveFile->close();
    mHighScore = score;
}

void ScoreSystem::saveHighScore()
{
    auto fileSystem = IOCContainer::instance().resolve<IFileSystem>();
    auto saveFile = fileSystem->loadFile("highscore.txt", true);
    if (!saveFile->isOpen())
    {
        auto dataDirectory = fileSystem->getAssetsDirectory();
        saveFile->create(dataDirectory + "highscore.txt");
    }
    auto fileHandle = saveFile->get();
    auto bytesWritten = fprintf(fileHandle, "%d", mHighScore);
    saveFile->close();
}
