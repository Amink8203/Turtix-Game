#ifndef _GROUND_HPP
#define _GROUND_HPP
#include "Tile.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

class Ground : public Tile
{
private:

public:
    Ground(Texture &_texture, int x, int y);
};
#endif