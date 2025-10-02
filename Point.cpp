#include "Point.hpp"
Point::Point(point_types type)
    : Animated(2)
{
    // in true va false ha ro check kon!
    Texture texture;
    if (type == STAR)
    {
        int rand_num = rand() % 2;
        if (rand_num == 0)
        {
            texture.loadFromFile("sprite/star1.png");
            set_frame(4, 16, 125, 125, true, STAR, ANIMATED_SPRITE_SCALE_FACTOR, texture);
        }
        else
        {
            texture.loadFromFile("sprite/star2.png");
            set_frame(4, 16, 125, 125, true, STAR, ANIMATED_SPRITE_SCALE_FACTOR, texture);
        }
        current_state = STAR;
    }
    else if (type == DIAMOND)
    {
        int rand_num = rand() % 2;
        if (rand_num == 0)
        {
            texture.loadFromFile("sprite/diamond1.png");
            set_frame(4, 16, 100, 100, true, DIAMOND, ANIMATED_SPRITE_SCALE_FACTOR, texture);
        }
        else
        {
            texture.loadFromFile("sprite/diamond2.png");
            set_frame(4, 16, 100, 100, true, DIAMOND, ANIMATED_SPRITE_SCALE_FACTOR, texture);
        }
        current_state = DIAMOND;
    }
    point = TYPES_POINTS[type];
}

void Point::animate_point()
{
    Animated::animate(false);
}

void Point::update()
{
    animate_point();
}

int Point::get_point()
{
    return point;
}
