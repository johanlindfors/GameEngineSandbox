#pragma once
#include <vector>
#include <memory>

namespace Utilities {
    class ILazyInitialized {
    public:
	    virtual void LazyInitialize() = 0;
    };
    
    typedef std::vector<std::shared_ptr<Utilities::ILazyInitialized>> LazyInitializedTypes;
}
