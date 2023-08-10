#pragma once
#include "resources/Texture2D.hpp"
#include "utilities/MathHelper.hpp"

struct DirectionComponent {
    int x;
	int y;
};

struct StaticComponent { };

struct InputComponent { };

struct SpawnComponent { };

struct CleanupComponent { 
	int counter;
};

struct PositionComponent {
	int x;
	int y;
};

struct SpriteComponent {
	Engine::Texture2D texture;
	Utilities::Point<float> position;
};
