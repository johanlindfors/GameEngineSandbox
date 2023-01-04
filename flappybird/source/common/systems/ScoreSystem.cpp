#include "ScoreSystem.h"
#include "utilities/IOC.hpp"
#include "filesystem/IFileSystem.h"
#include "File.h"
#include <stdio.h>

using namespace Engine;
using namespace Utilities;

void ScoreSystem::setLatestScore(int score) { 
    mLatestScore = score;
    if(mLatestScore > mHighScore) {
        mHighScore = mLatestScore;
        saveHighScore();
        printf("[ScoreSystem::SetLatestScore] HighScore saved: %d\n", mHighScore);
    }
};

void ScoreSystem::lazyInitialize() 
{
    loadHighScore();
    printf("[ScoreSystem::LazyInitialize] HighScore is: %d\n", mHighScore);
}

void ScoreSystem::loadHighScore()
{
    auto fileSystem = IOCContainer::instance().resolve<IFileSystem>();
    auto saveFile = fileSystem->loadFile("highscore.txt", false);
    int score = 0;
    if(saveFile->isOpen()) {
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
    if(!saveFile->isOpen()) {
        auto dataDirectory = fileSystem->getResourcesDirectory();        
        saveFile->create(dataDirectory + "highscore.txt");
    }
    auto fileHandle = saveFile->get();
    auto bytesWritten = fprintf(fileHandle, "%d", mHighScore);
    saveFile->close();
}
