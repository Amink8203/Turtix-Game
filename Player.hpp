#ifndef _PLAYER_HPP
#define _PLAYER_HPP
#include "Animated.hpp"
#include "Constants.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

enum animation_states
{
    IDLE,
    FALLING,
    JUMPING,
    WALKING,
    SWINGING,
    PUSHING,
    PULLING,
    DAMAGED,
    IDLE_PULLING,
    IDLE_PUSHING,
    CLIMBING,
    ENTERING_PORTAL
};

class Player : public Animated
{
private:
    int hp;
    int point;
    bool was_last_direction_left;
    bool is_the_game_ending;
    bool has_the_game_ended;
    Clock jump_clock;
    Clock end_clock;
public:
    Player();
    void move();
    Vector2f update();
    void add_point(int value);
    void animate_player();
    void ghostify();
    //accessors
    int get_hp();
    int get_points();
    bool get_is_the_game_ending();
    //modifiers
    void set_last_direction(bool left);
    void decrease_hp();
    void reset_points();
};
#endif