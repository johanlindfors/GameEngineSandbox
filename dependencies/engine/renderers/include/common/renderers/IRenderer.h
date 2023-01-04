#pragma once

namespace Engine 
{
    class IRenderer {
        public:
            virtual void initialize() = 0;
            virtual void updateWindowSize(int width, int height) = 0;
		    virtual void clear() = 0;
    };
}