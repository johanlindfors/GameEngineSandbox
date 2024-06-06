#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.hpp"

namespace Engine
{
    class IRenderer;
}

namespace Utilities
{
    class IStepTimer;
}

class IResourceDownloaderCallback
{
public:
	virtual ~IResourceDownloaderCallback() = default;
	virtual void complete() = 0;
	virtual void error() = 0;
};

class ResourceDownloader
{
public:
    ResourceDownloader(
        IResourceDownloaderCallback* callbackInstance,  
        std::vector<std::string> resources)
    {
        mCallbackInstance = callbackInstance;
        mResources = resources;
    }
    virtual ~ResourceDownloader() {}
    void downloadNext();
    void reportError();
private:
    std::vector<std::string> mResources;
    int mFetchedResources = 0;
    IResourceDownloaderCallback* mCallbackInstance;
};

namespace HelloWorld::Scenes
{
    class BootScene : public Engine::GameScene, public IResourceDownloaderCallback
    {
    public:
        BootScene() { id = typeid(BootScene).name();}

        // Engine::GameScene
        void load() override;
        void unload() override;
        void updateScreenSize(int width, int height) override;
        void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
        void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

        // IRessourceDownloaderCallback
        void complete() override;
        void error() override;

    private:
        bool mResourcesLoaded = false;
    };
}
