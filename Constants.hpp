#ifndef _CNST_HPP
#define _CNST_HPP
#include <SFML/Window.hpp>
using namespace sf;
const int TYPES_POINTS[2] = {1000, 5000};
const int ANIMATION_MILLISECONDS_PER_FRAME = 150;
const int STAR_POINTS = 1000;
const int DIAMOND_POINTS = 5000;
const Vector2f SPRITE_BASE_LENGTH = {136.f, 136.f};
const Vector2f ANIMATED_SPRITE_SCALE_FACTOR = {0.1f, 0.1f};
const float TILE_SPRITE_SCALE_FACTOR = 0.1f;
const float PLAYER_JUMP_SECONDS = 1.75f;
const float COLLISION_PRECISION = 3.f;
const float PLAYER_SPEED = 50.f;
const float BABY_SPEED = 50.f;
const float ENEMY_SPEED = 25.f;
#endif