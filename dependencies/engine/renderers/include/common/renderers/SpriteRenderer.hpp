#pragma once
#include <memory>
#include "Renderer.hpp"
#include "utilities/glwrapper.hpp"
#include "utilities/MathHelper.hpp"

namespace Engine
{
    class Shader;
    class OrthographicCamera;
    struct Sprite;

    class SpriteRenderer : public Renderer
    {
    public:
        SpriteRenderer(
            std::shared_ptr<Engine::Shader> shader,
            std::shared_ptr<Engine::OrthographicCamera> camera);
        ~SpriteRenderer();

        virtual void initialize() override;
        virtual void updateWindowSize(int width, int height) override;
        void drawSprite(std::shared_ptr<Engine::Sprite> sprite);
        void drawSprite(std::shared_ptr<Engine::Sprite> sprite, Utilities::Point<float> position);
        void clear(float r, float g, float b, float a) override;

    private:
        GLuint mVAO, mVBO, mEBO;
        std::shared_ptr<Engine::OrthographicCamera> mCamera;
    };
}