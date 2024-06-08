#include "resources/ResourceDownloader.hpp"
#include <emscripten.h>
#include <utilities/IOC.hpp>
#include <utilities/Logger.hpp>

using namespace std;
using namespace Engine;
using Utilities::IOCContainer;

ResourceDownloader::~ResourceDownloader() {
    debuglog << "[ResourceDownloader::~ResourceDownloader] In destructor" << endl;
}

void onLoaded(const char* file) {
    debuglog << "[ResourceDownloader::onLoaded] Download next..." << endl;
    auto resourceDownloader = IOCContainer::instance().resolve<ResourceDownloader>();
    resourceDownloader->downloadNext();
}

void onError(const char* file) {
    debuglog << "[ResourceDownloader::onError] Download failed!!!" << endl;
    auto resourceDownloader = IOCContainer::instance().resolve<ResourceDownloader>();
    resourceDownloader->reportError();
}

void ResourceDownloader::downloadResources(const std::vector<std::string>& resources)
{
    debuglog << "[ResourceDownloader::downloadResources] In downloadResources" << endl;
    mResources = resources;
    downloadNext();
}

void ResourceDownloader::downloadNext()
{
    debuglog << "[ResourceDownloader::downloadNext] In downloadNext" << endl;
    if (mFetchedResources == mResources.size()) {
        mCompleted(true);
    } else {
        auto httpFileName = string("http://localhost:6931/") + string(mResources[mFetchedResources]);
        debuglog << "[ResourceDownloader::downloadNext] Fetching file '" << httpFileName << "' from server." << endl;
        emscripten_async_wget(
            httpFileName.c_str(), 
            mResources[mFetchedResources].c_str(),
            onLoaded,
            onError
        );
        mFetchedResources++;
    }
}

void ResourceDownloader::reportError()
{
    debuglog << "[ResourceDownloader::reportError] In reportError" << endl;
    mCompleted(false);
}
