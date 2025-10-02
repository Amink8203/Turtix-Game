#ifndef _ANIMATED_HPP
#define _ANIMATED_HPP
#include "Constants.hpp"
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

enum direction
{
    FORWARD = 1,
    BACKWARD = -1
};

enum moving_directions
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    JUMP
};

struct Frames
{
    Texture texture;
    int row_frames;
    int total_frames;
    int width;
    int height;
    Vector2f sprite_scale;
    bool does_animation_loop;
};

class Animated
{
protected:
    short int current_state;
    Clock animation_clock;
    Clock movement_clock;
    Sprite sprite;
    Vector2f get_current_frame_scale();
    void set_current_frame_scale(Vector2f new_scale);

private:
    std::vector<Frames> frames;
    short int frame_counter;
    IntRect frame_rect;
    direction animation_direction;
    int animation_mspf;
    bool is_key_pressed[5];
    bool has_state_changed;
    // Functions
    void change_direction();

public:
    Animated(int number_of_states);
    void spawn(Vector2f spawn_pos);
    void move(float x, float y);
    virtual void render(RenderTarget *window);
    void set_frame(int _row_frames, int _total_frames, int _width, int _height,
                   bool _does_aniamtion_loop, short int _state, Vector2f _scale, Texture _texture);
    virtual void animate(bool shall_reflect);
    void init_animation();
    void reset_movement_clock();
    void scale_based_on_reflection(bool shall_reflect);
    bool does_it_collide(FloatRect &collided);
    // accessors
    short int get_frame_counter();
    short int get_current_state();
    Vector2f get_position();
    bool get_is_key_pressed(moving_directions dir);
    FloatRect get_global_bounds();
    // modifiers
    void set_is_key_pressed(moving_directions dir, bool new_value);
    void change_state(short int new_state);
};
#endif