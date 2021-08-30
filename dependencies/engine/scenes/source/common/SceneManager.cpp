#include "scenes/SceneManager.h"
#include "IOC.hpp"
#include <string>

using namespace std;
using namespace Engine;

SceneManager::SceneManager()
	: mInitialized(false)
	, mScreenWidth(0)
	, mScreenHeight(0)
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
	mScreenWidth = width;
	mScreenHeight = height;

	if (!mInitialized || mScenes.size() == 0) {
		return;
	}

	for (auto const& scene : mScenes)
	{
		scene->UpdateScreenSize(width, height);
	}
}

void SceneManager::Update(std::shared_ptr<Utilities::IStepTimer> timer)
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
	// printf("[SceneManager::Update] Scenes updated\n");
}

void SceneManager::Draw(std::shared_ptr<Utilities::IStepTimer> timer)
{
	printf("[SceneManager::Draw] \n");
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
		scene->UpdateScreenSize(mScreenWidth, mScreenHeight);
	}

	mScenes.push_back(scene);
}

void SceneManager::RemoveScene(const type_info& sceneType)
{
	const std::string sceneId = sceneType.name();

	for (size_t i = 0; i < mScenes.size(); i++)
	{
		if (mScenes.at(i)->ID == sceneId) {
			auto scene = mScenes.at(i);
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
