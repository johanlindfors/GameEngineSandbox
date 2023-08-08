#pragma once
#include "resources/Texture2D.hpp"
#include "utilities/MathHelper.hpp"

struct direction_component {
    int x;
	int y;
};

struct static_component { };

struct input_component { };

struct spawn_component { };

struct cleanup_component { 
	int counter;
};

struct position_component {
	int x;
	int y;
};

struct sprite_component {
	Engine::Texture2D texture;
	Utilities::Point<float> position;
};
