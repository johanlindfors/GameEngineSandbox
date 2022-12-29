#pragma once
#include "GameScene.h"
#include "utilities/IStepTimer.h"
#include <memory>

namespace Engine {
    class IRenderer;
    
    class ISceneManager {
    public:
	    virtual ~ISceneManager() = default;
	    virtual void Initialize() = 0;
        virtual void UpdateScreenSize(int width, int height) = 0;
        virtual void Update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
        virtual void Draw(std::shared_ptr<IRenderer> renderer) = 0;
        virtual void AddScene(std::shared_ptr<GameScene> scene) = 0;
        virtual void RemoveScene(const std::type_info& sceneType) = 0;
    };
}
