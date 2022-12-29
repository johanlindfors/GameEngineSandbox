#include "RenderingScene.h"
#include "renderers/SimpleRenderer.h"

using namespace Sample;

void RenderingScene::Load() 
{

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
