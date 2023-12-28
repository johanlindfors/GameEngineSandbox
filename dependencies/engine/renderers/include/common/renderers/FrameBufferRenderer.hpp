#pragma once
#include <memory>
#include "utilities/glwrapper.hpp"

namespace Utilities
{
    struct Config;
}

namespace Engine
{
    class Shader;

    class FrameBufferRenderer
    {
    public:
        FrameBufferRenderer(std::shared_ptr<Engine::Shader> shader);
        ~FrameBufferRenderer();
        void initialize(std::shared_ptr<Utilities::Config> config);
        void updateScreenSize(int width, int height);
        void begin();
        void end();

    protected:
        std::shared_ptr<Engine::Shader> mShader;
        unsigned int quadVAO, quadVBO;
        unsigned int framebuffer;
        unsigned int rbo;
        unsigned int textureColorbuffer;
        unsigned int mWidth, mHeight;
        unsigned int mScreenWidth, mScreenHeight;
    };
}