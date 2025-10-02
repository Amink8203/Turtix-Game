#ifndef _DOUBLELIFE_ENEMY_HPP
#define _DOUBLELIFE_ENEMY_HPP
#include "Animated.hpp"
#include "Constants.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

enum double_animation{
    TWO_LIVES,
    ONE_LIFE
};

class DoublelifeEnemy: public Animated{
    private:
    int moving_state;
    bool temp;

    public:
    DoublelifeEnemy();
    Vector2f get_down();
    Clock clock;
    bool rotate;
    bool first_collision;
    void animate_double();
    void update_move();
    void update();


};


#endif