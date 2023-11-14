#include "GameOverScene.hpp"
#include "renderers/FontRenderer.hpp"
#include "utilities/IOC.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GameOverScene::GameOverScene(IGameStateCallback *gameCallback)
    : mGameOverText("Game Over"), mFontRenderer(IOCContainer::resolve_type<FontRenderer>())
{
    id = typeid(GameOverScene).name();
}

void GameOverScene::draw(shared_ptr<IRenderer> renderer)
{
    mFontRenderer->drawString(mGameOverText, FontRenderer::Alignment::Center, Point<float>{200, 200}, 2.0f);
}
