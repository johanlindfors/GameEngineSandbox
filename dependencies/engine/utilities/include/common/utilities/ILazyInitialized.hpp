#pragma once
#include <vector>
#include <memory>

namespace Utilities {
    class ILazyInitialized {
    public:
	    virtual void lazyInitialize() = 0;
    };
    
    typedef std::vector<std::shared_ptr<Utilities::ILazyInitialized>> LazyInitializedTypes;
}
