#ifndef _BABY_HPP
#define _BABY_HPP
#include"Animated.hpp"
#include "Constants.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

enum baby_states
{
    FROZEN,
    MOVING
};


class Baby : public Animated{
    private:
    bool is_frozen;
    bool is_first_move;

    
    public:
    int moving_state;
    bool baby_has_fallen;
    bool first_move_is_left;
    bool rotate;
    bool is_falling;
    Baby();

    void animate_baby();
    void update_move();
    void update();
    
};



#endif