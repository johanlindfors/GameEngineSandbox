#pragma once
#include "GameScene.h"
#include "IStepTimer.h"
#include <memory>
#include <string>

namespace Engine {
    
    class ISceneManager {
    public:
        virtual void Initialize() = 0;
        virtual void UpdateScreenSize(int width, int height) = 0;
        virtual void Update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
        virtual void Draw(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
        virtual void AddScene(std::shared_ptr<GameScene> scene) = 0;
        virtual void RemoveScene(const type_info& sceneType) = 0;
    };
}
