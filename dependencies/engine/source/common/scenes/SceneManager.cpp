#include "scenes/SceneManager.h"
#include "IOC.hpp"

using namespace std;
using namespace Engine;

SceneManager::SceneManager()
	: mInitialized(false)
{
	
}

void SceneManager::Initialize() 
{
	if (mInitialized) {
		return;
	}
	
	for (auto const& scene : mScenes)
	{
		scene->Load();
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

	mScenesToUpdate.clear();
	mScenesToUpdate = mScenes;

	for (auto const& scene : mScenesToUpdate)
	{
		if (scene) {
			scene->Update(timer);
		}
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
		scene->Load();
	}

	mScenes.push_back(scene);
}

void SceneManager::RemoveScene(const char* sceneId)
{
	shared_ptr<GameScene> scene;

	for (size_t i = 0; i < mScenes.size(); i++)
	{
		if (mScenes.at(i)->ID == sceneId) {
			scene = mScenes.at(i);
			scene->Unload();
			mScenes.erase(mScenes.begin() + i);
		}
	}

	for (size_t i = 0; i < mScenesToUpdate.size(); i++)
	{
		if (mScenesToUpdate.at(i)->ID == sceneId) {
			mScenesToUpdate.erase(mScenesToUpdate.begin() + i);
		}
	}
}
