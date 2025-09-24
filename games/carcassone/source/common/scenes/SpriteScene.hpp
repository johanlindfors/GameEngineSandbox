#pragma once
// thirdparty
#include <memory>
#include <vector>
// engine
#include "game/Components.hpp"
#include "game/systems/DirectionSystem.hpp"
#include "game/systems/PositionSystem.hpp"
#include "game/systems/TileSystem.hpp"
#include "game/systems/SpriteSystem.hpp"
#include "scenes/GameScene.hpp"

class IGameStateCallback;
namespace Engine
{
    class SpriteRenderer;
    class IInputManager;
    struct TiledSprite;
    class OrthographicCamera;
}

namespace Utilities
{
    class IStepTimer;
}

namespace Sample
{
    class SpriteScene : public Engine::GameScene
    {
    public:
        SpriteScene()
            : mSpriteSystem(std::make_unique<SpriteSystem>())
            , mPositionSystem(std::make_unique<PositionSystem>())
            , mTileSystem(std::make_unique<TileSystem>(mRegistry, true))
            , mDirectionSystem(std::make_unique<DirectionSystem>())
            , mMouseDownX(0), mMouseDownY(0), mLastButtonPressedTime(0)
        {
            id = typeid(SpriteScene).name();
        }

        // Engine::GameScene
        void load() override;
        void unload() override;
        void updateScreenSize(int width, int height) override;
        void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
        void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

    private:
        Utilities::Point<int> translateGameToGameBoardCoordinate(int x, int y);
        void prepareValidMoves();
        bool isAvaiableMove(int x, int y, int tile);
        bool isValidMove(int x, int y);
        void placeTile(int x, int y);
        void placeStartTile();
        std::shared_ptr<Engine::SpriteRenderer> mRenderer;
        std::shared_ptr<Engine::TiledSprite> mSprite;
        std::shared_ptr<Engine::IInputManager> mInputManager;
        std::shared_ptr<Engine::OrthographicCamera> mCamera;

        entt::registry mRegistry;
        entt::entity mCurrentTile;
        std::unique_ptr<SpriteSystem> mSpriteSystem;
        std::unique_ptr<PositionSystem> mPositionSystem;
        std::unique_ptr<TileSystem> mTileSystem;
        std::unique_ptr<DirectionSystem> mDirectionSystem;

        int mMouseDownX;
        int mMouseDownY;
        Utilities::Point<float> mCurrentTilePosition;
        double mLastButtonPressedTime;
        Utilities::Point<int> mLastPressedCell{0, 0};
    };
}
