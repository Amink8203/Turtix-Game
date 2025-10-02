#include "Ground.hpp"
Ground::Ground(Texture &_texture, int x, int y)
    : Tile(64, 26, 168, 168, x, y)
{
    texture = _texture;
}