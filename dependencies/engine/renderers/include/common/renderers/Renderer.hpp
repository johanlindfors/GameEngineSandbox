#pragma once
#include <memory>
#include "IRenderer.hpp"
#include "utilities/glwrapper.hpp"
#include "utilities/MathHelper.hpp"

namespace Engine
{
    class Shader;

    class Renderer : public IRenderer
    {
    public:
        Renderer(std::shared_ptr<Engine::Shader> shader);
        ~Renderer();
        virtual void initialize();
        virtual void updateWindowSize(int width, int height);
        virtual void clear();
        virtual void clear(float r, float g, float b, float a);

    protected:
        std::shared_ptr<Engine::Shader> mShader;
    };
}