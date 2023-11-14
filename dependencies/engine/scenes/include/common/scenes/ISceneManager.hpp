#pragma once
#include "GameScene.hpp"
#include "utilities/IStepTimer.hpp"
#include <memory>

namespace Engine
{
    class IRenderer;

    class ISceneManager
    {
    public:
        virtual ~ISceneManager() = default;
        virtual void initialize() = 0;
        virtual void updateScreenSize(int width, int height) = 0;
        virtual void update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
        virtual void draw(std::shared_ptr<IRenderer> renderer) = 0;
        virtual void addScene(std::shared_ptr<GameScene> scene) = 0;
        virtual void removeScene(const std::type_info &sceneType) = 0;
    };
}
