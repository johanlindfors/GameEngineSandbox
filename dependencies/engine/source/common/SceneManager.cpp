#include "SceneManager.h"

using namespace std;

SceneManager::SceneManager()
	: mInitialized(false)
{

}

void SceneManager::Initialize() 
{
	if (mInitialized) {
		return;
	}
	mInitialized = true;
}

void SceneManager::UpdateScreenSize(int width, int height)
{
	if (!mInitialized || mScenes.size() == 0) {
		return;
	}

	for (auto const& scene : mScenes)
	{
		scene->UpdateScreenSize(width, height);
	}
}

void SceneManager::Update(Utilities::StepTimer const& timer) 
{
	if (!mInitialized || mScenes.size() == 0) {
		return;
	}

	for (auto const& scene : mScenes)
	{
		scene->Update(timer);
	}
}

void SceneManager::Draw(Utilities::StepTimer const& timer)
{
	if (!mInitialized || mScenes.size() == 0) {
		return;
	}

	for (auto const& scene : mScenes)
	{
		scene->Draw(timer);
	}
}

void SceneManager::AddScene(shared_ptr<GameScene> scene)
{
	if (mInitialized) {
		//scene->LoadContent();
	}

	mScenes.push_back(scene);
}

void SceneManager::RemoveScene(shared_ptr<GameScene> scene)
{
	if (mInitialized) {
		//scene->UnloadContent();
	}

	for (size_t i = 0; i < mScenes.size(); i++)
	{
		if (mScenes.at(i) == scene) {
			mScenes.erase(mScenes.begin() + i);
		}
	}

	for (size_t i = 0; i < mScenes.size(); i++)
	{
		if (mScenesToUpdate.at(i) == scene) {
			mScenesToUpdate.erase(mScenesToUpdate.begin() + i);
		}
	}

}
