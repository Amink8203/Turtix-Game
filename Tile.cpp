#include "Tile.hpp"
Tile::Tile(int left, int top, int width, int height, int x, int y)
{
    rect.top = top;
    rect.left = left;
    rect.width = width;
    rect.height = height;
    tile_scale_factor = TILE_SPRITE_SCALE_FACTOR;
    sprite.setScale(TILE_SPRITE_SCALE_FACTOR, TILE_SPRITE_SCALE_FACTOR);
    sprite.setPosition(x * rect.width * TILE_SPRITE_SCALE_FACTOR,
                       y * rect.height * TILE_SPRITE_SCALE_FACTOR);
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
}
void Tile::render(RenderTarget *window)
{
    window->draw(sprite);
}
// accessors
IntRect Tile::get_rect()
{
    return sprite.getTextureRect();
}
FloatRect Tile::get_global_bounds()
{
    return sprite.getGlobalBounds();
}
Vector2f Tile::get_position()
{
    Vector2f pos = sprite.getPosition();
    pos.x += sprite.getGlobalBounds().width / 2;
    pos.y += sprite.getGlobalBounds().height;
    return pos;
}

Vector2i Tile::get_top_middle()
{
    Vector2i pos;
    pos.x = sprite.getPosition().x + sprite.getTextureRect().width / 2;
    pos.y = sprite.getPosition().y;
    return pos;
}

bool Tile::does_it_collide(FloatRect &collided)
{
    return sprite.getGlobalBounds().intersects(collided);
}

bool Tile::does_it_contain(Vector2f pos)
{
    return sprite.getGlobalBounds().contains(pos);
}
