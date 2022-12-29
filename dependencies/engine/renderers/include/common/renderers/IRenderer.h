#pragma once

namespace Engine 
{
    class IRenderer {
        public:
            virtual void Initialize() = 0;
            virtual void UpdateWindowSize(int width, int height) = 0;
		    virtual void Clear() = 0;
    };
}