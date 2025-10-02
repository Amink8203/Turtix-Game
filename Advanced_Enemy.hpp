#ifndef _ADVANCED_ENEMY_HPP
#define _ADVANCED_ENEMY_HPP
#include "Animated.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

enum advanced_animation
{
    ORDINARY,
    UNBEATABLE
};

class AdvancedEnemy : public Animated
{
private:
    int moving_state;

public:
    AdvancedEnemy();
    Vector2f get_down();
    Clock player_clock;
    Clock enemy_clock;
    bool is_unbeatable;
    bool rotate;
    void animate_advanced();
    void update_move();
    void update();
};

#endif