#include "SpriteScene.hpp"
// thirdparty
// engine
#include "input/IInputManager.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Camera.hpp"
#include "resources/IResourceManager.hpp"
#include "resources/Shader.hpp"
#include "scenes/ISceneManager.hpp"
#include "sprites/TiledSprite.hpp"
#include "utilities/Config.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/StepTimer.hpp"
// game

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace Sample;

void SpriteScene::load()
{
    debuglog << "[SpriteScene::load]" << std::endl;
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();

    resourceManager->loadShader("simple", "simple.vs", "simple.fs");
    resourceManager->loadTextures({"tiles_sample.png"});
    mSpriteSystem->setTexture(resourceManager->getTexture("tiles_sample.png"));

    auto config = IOCContainer::instance().resolve<Utilities::Config>();
    mCamera = make_shared<Engine::OrthographicCamera>(0.0f, config->width, 0.0f, config->height, -1.0f, 1.0f);
    auto shader = resourceManager->getShader("simple");
    mRenderer = make_shared<SpriteRenderer>(shader, mCamera);
    mRenderer->initialize();

    IOCContainer::instance().register_type<IRenderer>(mRenderer);

    mInputManager = IOCContainer::instance().resolve<IInputManager>();

    placeStartTile();
    prepareValidMoves();
}

void SpriteScene::prepareValidMoves()
{
    auto validMovesView = mRegistry.view<ValidMoveComponent>();
    mRegistry.destroy(validMovesView.begin(), validMovesView.end());

    auto placedTilesView = mRegistry.view<PositionComponent>();
    debuglog << "[SpriteScene::prepareValidMoves] Number of tiles on board: " << placedTilesView.size() << std::endl;

    for (auto entity : placedTilesView)
    {
        auto position = placedTilesView.get<PositionComponent>(entity);
        std::vector<std::pair<int, int>> directions = {
            {position.x, position.y + 1},
            {position.x + 1, position.y},
            {position.x, position.y - 1},
            {position.x - 1, position.y}};

        for (auto dir : directions)
        {
            if (isAvaiableMove(dir.first, dir.second, 0))
            {
                auto validMove = mRegistry.create();
                mRegistry.emplace<ValidMoveComponent>(validMove, dir.first, dir.second);
                mRegistry.emplace<SpriteComponent>(validMove, 24);
            }
        }
    }
    debuglog << "[SpriteScene::isValidMove] Number of validMoves on board: " << validMovesView.size() << std::endl;
}

bool SpriteScene::isAvaiableMove(int x, int y, int tile)
{
    auto placedTilesView = mRegistry.view<PositionComponent>();
    for (auto entity : placedTilesView)
    {
        auto [position] = placedTilesView.get(entity);
        if (position.x == x && position.y == y)
        {
            return false;
        }
    };
    return true;
}

void SpriteScene::placeStartTile()
{
    auto tile = mTileSystem->getNextTile(mRegistry);
    mRegistry.emplace<PositionComponent>(tile, 0, 0);
    mRegistry.erase<StartComponent>(tile);
}

bool SpriteScene::isValidMove(int x, int y)
{
    auto validMovesView = mRegistry.view<ValidMoveComponent>();
    for (auto entity : validMovesView)
    {
        auto [position] = validMovesView.get(entity);
        if (position.x == x && position.y == y)
        {
            return true;
        }
    };
    return false;
}

void SpriteScene::placeTile(int x, int y, int frame)
{
    auto offset = mPositionSystem->getViewOffset();
    int xPos = x - offset.x;
    int yPos = y - offset.y;
    xPos = (int)((xPos + TILE_WIDTH / (xPos >= 0 ? 2 : -2)) / TILE_WIDTH);
    yPos = (int)((yPos + TILE_HEIGHT / (yPos >= 0 ? 2 : -2)) / TILE_HEIGHT);

    if (isValidMove(xPos, yPos))
    {
        debuglog << "[SpriteScene::placeTile] Valid position!" << std::endl;
        auto tile = mTileSystem->getNextTile(mRegistry);
        mRegistry.emplace<PositionComponent>(tile, xPos, yPos);
        mRegistry.replace<DirectionComponent>(tile, (Direction)(rand() % 4));

        prepareValidMoves();
    }
    // int count = 0;
    // mRegistry.view<SpriteComponent>(entt::exclude<ValidMoveComponent>).each([&count](auto entity) {
    //     count+=1;
    // });
    // debuglog << "[SpriteScene::placeTile] Number of tiles: " << count << std::endl;
}

void SpriteScene::unload()
{
    debuglog << "[SpriteScene::unload]" << std::endl;
    mRenderer.reset();
}

void SpriteScene::updateScreenSize(int width, int height)
{
    debuglog << "[SpriteScene::updateScreenSize]" << std::endl;
    mCamera->right = width;
    mCamera->top = height;

    mPositionSystem->updateScreenSize(width, height);
}

void SpriteScene::update(shared_ptr<IStepTimer> timer)
{
    auto const mouseState = mInputManager->getMouseState();
    auto translatedCoordinate = mCamera->translateScreenToGameCoordinate(
        mouseState.position.x,
        mouseState.position.y);
    switch (mouseState.state)
    {
    case ButtonState::Pressed:
        placeTile(
            translatedCoordinate.x,
            translatedCoordinate.y,
            rand() % 24);
        mMouseDownX = mouseState.position.x;
        mMouseDownY = mouseState.position.y;
        break;
    case ButtonState::Repeat:
        mPositionSystem->setMouseMoveOffset(
            mMouseDownX != 0 ? mouseState.position.x - mMouseDownX : mMouseDownX,
            mMouseDownY != 0 ? mouseState.position.y - mMouseDownY : mMouseDownY);
        mMouseDownX = mouseState.position.x;
        mMouseDownY = mouseState.position.y;
        break;

    default:
        mMouseDownX = 0;
        mMouseDownY = 0;
        break;
    }

    mPositionSystem->update(mRegistry);
    mDirectionSystem->update(mRegistry);
}

void SpriteScene::draw(shared_ptr<IRenderer> renderer)
{
    mRenderer->clear(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    mSpriteSystem->render(mRegistry, mRenderer);
}
