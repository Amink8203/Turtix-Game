#include "Portal.hpp"
Portal::Portal(int x, int y)
    : Tile(109, 0, 168, 168, x, y)
{
    texture.loadFromFile("sprite/closed_portal.png");
    is_portal_open = false;
}

void Portal::change_portal()
{
    is_portal_open = true;
    texture.loadFromFile("sprite/open_portal.png");
}

bool Portal::get_is_portal_open()
{
    return is_portal_open;
}