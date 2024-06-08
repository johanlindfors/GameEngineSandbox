#pragma once
#include <functional>
#include <vector>
#include <string>

namespace Engine
{
    class ResourceDownloader
    {
    public:
        ResourceDownloader(
            std::function<void(bool)> completed,
            std::function<void(int)> progress)
            : mCompleted(completed)
            , mProgress(progress) {}
        
        virtual ~ResourceDownloader() {}
        void downloadResources(const std::vector<std::string>& resources);
        void downloadNext();
        void reportError();
        
    private:
        std::vector<std::string> mResources;
        std::function<void(bool)> mCompleted;
        std::function<void(int)> mProgress;
        int mFetchedResources = 0;
    };
}
