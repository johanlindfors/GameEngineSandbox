#include "scenes/SceneManager.hpp"
#include "utilities/IOC.hpp"
#include "renderers/ISpriteRenderer.hpp"
#include <string>

using namespace std;
using namespace Engine;

SceneManager::SceneManager()
	: mInitialized(false)
	, mScreenWidth(0)
	, mScreenHeight(0) { }

SceneManager::~SceneManager()
{
	printf("[SceneManager::~SceneManager]\n");
	for (auto & scene : mScenes)
	{
		scene->unload();
		scene.reset();
	}
}

void SceneManager::initialize() 
{
	if (mInitialized) {
		return;
	}
	
	for (auto const& scene : mScenes)
	{
		scene->load();
	}
	mInitialized = true;
}

void SceneManager::updateScreenSize(int width, int height)
{
	mScreenWidth = width;
	mScreenHeight = height;

	if (!mInitialized || mScenes.size() == 0) {
		return;
	}

	for (auto const& scene : mScenes)
	{
		scene->updateScreenSize(width, height);
	}
}

void SceneManager::update(std::shared_ptr<Utilities::IStepTimer> timer)
{
	if (!mInitialized || mScenes.size() == 0) {
		return;
	}

	mScenesToUpdate.clear();
	mScenesToUpdate = mScenes;

	for (auto const& scene : mScenesToUpdate)
	{
		if (scene) {
			scene->update(timer);
		}
	}
}

void SceneManager::draw(shared_ptr<IRenderer> renderer)
{
	if (!mInitialized || mScenes.size() == 0) {
		return;
	}

	for (auto const& scene : mScenes)
	{
		scene->draw(renderer);
	}
}

void SceneManager::addScene(shared_ptr<GameScene> scene)
{
	if (mInitialized) {
		scene->load();
		scene->updateScreenSize(mScreenWidth, mScreenHeight);
	}

	mScenes.push_back(scene);
}

void SceneManager::removeScene(const type_info& sceneType)
{
	const std::string sceneId = sceneType.name();

	for (size_t i = 0; i < mScenes.size(); i++)
	{
		if (mScenes.at(i)->id == sceneId) {
			auto scene = mScenes.at(i);
			scene->unload();
			mScenes.erase(mScenes.begin() + i);
		}
	}

	for (size_t i = 0; i < mScenesToUpdate.size(); i++)
	{
		if (mScenesToUpdate.at(i)->id == sceneId) {
			mScenesToUpdate.erase(mScenesToUpdate.begin() + i);
		}
	}
}
