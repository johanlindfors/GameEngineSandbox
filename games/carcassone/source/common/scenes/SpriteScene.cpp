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

    mCurrentTilePosition = { TILE_WIDTH / 2, mCamera->top - TILE_HEIGHT * 1.5f };

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
    mCurrentTile = mTileSystem->getNextTile(mRegistry);
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

void SpriteScene::placeTile(int x, int y)
{
    auto offset = mPositionSystem->getViewOffset();
    int xPos = x - offset.x;
    int yPos = y - offset.y;
    auto result = translateGameToGameBoardCoordinate(xPos, yPos);

    if (isValidMove(result.x, result.y))
    {
        debuglog << "[SpriteScene::placeTile] Valid position!" << std::endl;
        mRegistry.emplace<PositionComponent>(mCurrentTile, result.x, result.y);
        mRegistry.replace<DirectionComponent>(mCurrentTile, (Direction)(rand() % 4));

        prepareValidMoves();
        mCurrentTile = mTileSystem->getNextTile(mRegistry);
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
    mCurrentTilePosition = { TILE_WIDTH / 2, mCamera->top - TILE_HEIGHT * 1.5f };
}

Point<int> SpriteScene::translateGameToGameBoardCoordinate(int x, int y)
{
    return {(int)((x + TILE_WIDTH / (x >= 0 ? 2 : -2)) / TILE_WIDTH),
            (int)((y + TILE_HEIGHT / (y >= 0 ? 2 : -2)) / TILE_HEIGHT)};
}

void SpriteScene::update(shared_ptr<IStepTimer> timer)
{
    mLastButtonPressedTime += timer->getDeltaMicroSeconds() / 1000;
    
    auto const mouseState = mInputManager->getMouseState();
    
    auto translatedCoordinate = mCamera->translateScreenToGameCoordinate(
        mouseState.position.x,
        mouseState.position.y);
    auto pressedCell = translateGameToGameBoardCoordinate(
            static_cast<int>(translatedCoordinate.x),
            static_cast<int>(translatedCoordinate.y));
    switch (mouseState.state)
    {
    case ButtonState::Pressed:
        debuglog << "[SpriteScene::update] Elapsed seconds: " << mLastButtonPressedTime << std::endl;
        if(mLastButtonPressedTime < 250 && pressedCell == mLastPressedCell) {
            placeTile(
                translatedCoordinate.x,
                translatedCoordinate.y);
        }
        mMouseDownX = mouseState.position.x;
        mMouseDownY = mouseState.position.y;
        mLastButtonPressedTime = 0;
        mLastPressedCell = pressedCell;
        break;

    case ButtonState::Repeat:
        mPositionSystem->setMouseMoveOffset(
            mMouseDownX != 0 ? mouseState.position.x - mMouseDownX : mMouseDownX,
            mMouseDownY != 0 ? mouseState.position.y - mMouseDownY : mMouseDownY);
        mMouseDownX = mouseState.position.x;
        mMouseDownY = mouseState.position.y;
        break;

    case ButtonState::Released:
    case ButtonState::None:
        mMouseDownX = 0;
        mMouseDownY = 0;
        break;
    }

    mPositionSystem->update(mRegistry);
    mDirectionSystem->update(mRegistry);
    if(mLastButtonPressedTime > 2000) {
        mLastButtonPressedTime -= 1000;
    }
}

void SpriteScene::draw(shared_ptr<IRenderer> renderer)
{
    mRenderer->clear(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    mSpriteSystem->render(mRegistry, mRenderer, mCurrentTile, mCurrentTilePosition);
}
