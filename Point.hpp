#ifndef _POINT_HPP
#define _POINT_HPP
#include "Animated.hpp"
#include "Constants.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

enum point_types
{
    STAR,
    DIAMOND
};

class Point : public Animated
{
private:
    int point;
public:
    Point(point_types type);
    bool first_move_is_left;
    void animate_point();
    void update();
    //accessors
    int get_point();
};
#endif