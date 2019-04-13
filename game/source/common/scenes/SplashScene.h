#pragma once
#include "scenes/GameScene.h"
#include "textures/ITextureManager.h"

class SplashScene : public GameScene 
{
public:
    SplashScene();
    ~SplashScene();
    void Load();
	void Unload();
	void UpdateScreenSize(int width, int height);
	void Update(Utilities::StepTimer const& timer);
	void Draw(Utilities::StepTimer const& timer);

private:
	std::shared_ptr<ITextureManager> mTextureManager;
};