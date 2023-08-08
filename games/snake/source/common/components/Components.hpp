#pragma once
#include "resources/Texture2D.hpp"
#include "utilities/MathHelper.hpp"

struct direction_component {
    int x;
	int y;
};

struct input_component { };

struct position_component {
	int x;
	int y;
};

struct sprite_component {
	Engine::Texture2D texture;
	Utilities::Point<float> position;
};