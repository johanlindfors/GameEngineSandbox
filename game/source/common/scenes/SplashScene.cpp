#include "SplashScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"

using namespace std;

SplashScene::SplashScene() 
{

}

SplashScene::~SplashScene()
{

}

void SplashScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();

	vector<wstring> filenames;
	filenames.emplace_back(L"file.png");
	filenames.emplace_back(L"file2.png");
	mTextureManager->LoadTextures(vector<wstring>(filenames));
}

void SplashScene::Unload()
{

}

void SplashScene::UpdateScreenSize(int width, int height) 
{

}

void SplashScene::Update(Utilities::StepTimer const& timer)
{

}

void SplashScene::Draw(Utilities::StepTimer const& timer)
{
    
}