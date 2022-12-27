#include "ScoreSystem.h"
#include "utilities/IOC.hpp"
#include "filesystem/IFileSystem.h"
#include "File.h"
#include <stdio.h>

using namespace Engine;
using namespace Utilities;

void ScoreSystem::SetLatestScore(int score) { 
    mLatestScore = score;
    if(mLatestScore > mHighScore) {
        mHighScore = mLatestScore;
        SaveHighScore();
        printf("[ScoreSystem::SetLatestScore] HighScore saved: %d\n", mHighScore);
    }
};

void ScoreSystem::LazyInitialize() 
{
    LoadHighScore();
    printf("[ScoreSystem::LazyInitialize] HighScore is: %d\n", mHighScore);
}

void ScoreSystem::LoadHighScore()
{
    auto fileSystem = IOCContainer::Instance().Resolve<IFileSystem>();
    auto saveFile = fileSystem->LoadFile("highscore.txt", false);
    int score = 0;
    if(saveFile->IsOpen()) {
		auto fileHandle = saveFile->Get();
        fscanf(fileHandle, "%d", &score);
    }
    saveFile->Close();
    mHighScore = score;
}

void ScoreSystem::SaveHighScore()
{
    auto fileSystem = IOCContainer::Instance().Resolve<IFileSystem>();
    auto saveFile = fileSystem->LoadFile("highscore.txt", true);
    if(!saveFile->IsOpen()) {
        auto dataDirectory = fileSystem->GetResourcesDirectory();        
        saveFile->Create(dataDirectory + "highscore.txt");
    }
    auto fileHandle = saveFile->Get();
    auto bytesWritten = fprintf(fileHandle, "%d", mHighScore);
    saveFile->Close();
}
