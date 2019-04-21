#pragma once
#include "scenes/GameScene.h"
#include "textures/ITextureManager.h"
#include "sprites/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "MathHelper.h"
#include <ctime>
#include <list>

#define INITIAL_TAIL 5
#define SPRITE_SIZE 20
#define SCREEN_SIZE 20
#define FRAMES_PER_SECOND 15
#define INITIAL_TAIL 5

class Entity {
public:
	Entity(Utilities::Vector2 position)
	{
		mSprite.Position = position;
	}

	void SetTexture(Engine::Texture2D texture) 
	{
		mSprite.Texture = texture;
	}

	void Update(int screenWidth, int screenHeight)
	{
		mSprite.Width = screenWidth / SCREEN_SIZE - 1;
		mSprite.Height = screenHeight / SCREEN_SIZE - 1;
	}

protected:
	Engine::Sprite mSprite;
};

class Snake : public Entity {
public:
	Snake(Utilities::Vector2 position)
		: Entity(position)
	{
		mTail = INITIAL_TAIL;	
		mSprite.Position = Utilities::Vector2(10.0f, 10.0f);
		mSprite.Velocity = Utilities::Vector2(0.0f, 1.0f);
	}

	bool CheckCollision(int x, int y) {
		for (auto const& body : mTrail) {
			if (body.m[0] == x && body.m[1] == y) {
				return true;
			}
		}
		return false;
	}

	void Update(int screenWidth, int screenHeight) 
	{
		Entity::Update(screenWidth, screenHeight);

		mSprite.Position.m[0] = static_cast<int>(mSprite.Position.m[0] + mSprite.Velocity.m[0] + SCREEN_SIZE) % SCREEN_SIZE;
		mSprite.Position.m[1] = static_cast<int>(mSprite.Position.m[1] + mSprite.Velocity.m[1] + SCREEN_SIZE) % SCREEN_SIZE;

		mTrail.push_back({ mSprite.Position.m[0] * screenWidth/ SCREEN_SIZE, mSprite.Position.m[1] * screenHeight / SCREEN_SIZE });
		while (mTrail.size() > mTail) {
			mTrail.pop_front();
		}
	}
	
	void HandleInput(std::shared_ptr<Engine::IInputManager> input)
	{
		if (input->IsKeyDown(40)) {
			mSprite.Velocity = Utilities::Vector2(0.0f, 1.0f);
		}
		if (input->IsKeyDown(38)) {
			mSprite.Velocity = Utilities::Vector2(0.0f, -1.0f);
		}
		if (input->IsKeyDown(37)) {
			mSprite.Velocity = Utilities::Vector2(-1.0f, 0.0f);
		}
		if (input->IsKeyDown(39)) {
			mSprite.Velocity = Utilities::Vector2(1.0f, 0.0f);
		}
	}

	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer) {
		for (auto const& body : mTrail)
		{
			auto sprite = mSprite;
			sprite.Position = body;
			renderer->DrawSprite(sprite);
		}
	}

private:
	int mTail;
	std::list<Utilities::Vector2> mTrail;
};

class Apple : public Entity {
public:
	Apple(Utilities::Vector2 position)
		: Entity(position)
		, mScreenPosition(Utilities::Vector2(0.0f, 0.0f))
	{ }

	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer) {
		auto sprite = mSprite;
		sprite.Position = mScreenPosition;
		renderer->DrawSprite(sprite);
	}

	void Update(int screenWidth, int screenHeight)
	{
		Entity::Update(screenWidth, screenHeight);

		mScreenPosition = Utilities::Vector2({ mSprite.Position.m[0] * screenWidth / SCREEN_SIZE, mSprite.Position.m[1] * screenHeight / SCREEN_SIZE });
	}

private:
	Utilities::Vector2 mScreenPosition;
};

class GamePlayScene : public Engine::GameScene 
{
public:
    GamePlayScene();
    ~GamePlayScene();
    void Load();
	void Unload();
	void UpdateScreenSize(int width, int height);
	void Update(Utilities::StepTimer const& timer);
	void Draw(Utilities::StepTimer const& timer);

private:
	void HandleInput();

	std::shared_ptr<Apple> mApple;
	std::shared_ptr<Snake> mSnake;

	std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
	std::shared_ptr<Engine::IInputManager> mInputManager;
	int mScreenSizeX;
	int mScreenSizeY;
};