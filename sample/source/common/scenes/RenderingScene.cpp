#include "RenderingScene.h"
#include "renderers/SimpleRenderer.h"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.h"

using namespace Sample;
using namespace Engine;
using namespace Utilities;

void RenderingScene::Load() 
{
    auto resourceManager = IOCContainer::Instance().Resolve<IResourceManager>();
    resourceManager->LoadShader("basic_lighting", "basic_lighting.vs", "basic_lighting.fs");
	resourceManager->LoadShader("light_cube", "light_cube.vs", "light_cube.fs");
}

void RenderingScene::Unload() 
{ 

}

void RenderingScene::UpdateScreenSize(int width, int height) { }

void RenderingScene::Update(std::shared_ptr<Utilities::IStepTimer> timer) { }

void RenderingScene::Draw(std::shared_ptr<Engine::IRenderer> renderer) { 
    auto pRenderer = renderer.get();
    auto simpleRenderer = (Engine::SimpleRenderer*)(void*)pRenderer;
    simpleRenderer->Draw();
}
