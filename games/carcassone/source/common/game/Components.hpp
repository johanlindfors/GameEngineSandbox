#pragma once
#include "resources/Texture2D.hpp"
#include "utilities/MathHelper.hpp"

enum TileType {
    Field,
    Road,
    City,
    River
};

struct TileTypeComponent {
    TileType north;
    TileType south;
    TileType east;
    TileType west;
    TileType center;
};

struct PositionComponent {
	int x;
	int y;
};

enum MeepleStyle {
    None = 0,
    Farmer
};

enum MeepleColor {
    Red,
    Green,
    Blue,
    Yellow,
    Black
};

struct MeepleComponent {
    MeepleColor color;
    MeepleStyle style;
};

enum Direction {
    North,
    East,
    South,
    West
};

struct DirectionComponent {
    Direction direction;
};

struct StaticComponent { };

struct CloisterComponent { };

struct BadgeComponent { };

struct SpriteComponent {
	Engine::Texture2D texture;
    int frame;
	Utilities::Point<float> position;
};
