#ifndef _PORTAL_HPP
#define _PORTAL_HPP
#include "Tile.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

class Portal : public Tile
{
private:
    bool is_portal_open;

public:
    Portal(int x, int y);
    // accessors
    bool get_is_portal_open();
    // modifiers
    void change_portal();
};
#endif