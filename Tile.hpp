#ifndef _TILE_HPP
#define _TILE_HPP
#include "Constants.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

class Tile
{
protected:
    Texture texture;

private:
    Sprite sprite;
    IntRect rect;
    float tile_scale_factor;

public:
    Tile();
    Tile(int left, int top, int width, int height, int x, int y);
    void render(RenderTarget *window);
    // accessors
    IntRect get_rect();
    FloatRect get_global_bounds();
    Vector2f get_position();
    Vector2i get_top_middle();
    bool does_it_collide(FloatRect &collided);
    bool does_it_contain(Vector2f pos);
};
#endif