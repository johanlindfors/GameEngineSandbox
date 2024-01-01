#include "GameOverScene.hpp"
#include "renderers/FontRenderer.hpp"
#include "utilities/IOC.hpp"

using namespace std;
using namespace Engine;
using namespace Engine;

GameOverScene::GameOverScene(IGameStateCallback *gameCallback)
    : mGameOverText("Game Over"), mFontRenderer(IOCContainer::resolve_type<FontRenderer>())
{
    id = typeid(GameOverScene).name();
}

void GameOverScene::draw(shared_ptr<IRenderer> renderer)
{
    renderer->clear();

    mFontRenderer->drawString(mGameOverText, FontRenderer::Alignment::Center, Point<float>{200, 200}, 2.0f);
}
