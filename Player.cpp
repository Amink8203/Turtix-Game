#include "Player.hpp"
Player::Player()
    : Animated(12)
{
    Texture texture; // inaro tagheer dady
    texture.loadFromFile("sprite/walking.png");
    set_frame(1, 1, 136, 136, true, IDLE, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    set_frame(1, 8, 136, 136, true, FALLING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    set_frame(5, 5, 136, 136, false, JUMPING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    set_frame(5, 5, 136, 136, false, WALKING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/swinging.png");
    set_frame(5, 16, 96, 96, true, SWINGING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/pushing.png");
    set_frame(5, 16, 96, 96, true, PUSHING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/pulling.png");
    set_frame(5, 16, 96, 96, true, PULLING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/damaged.png");
    set_frame(4, 4, 192, 192, false, DAMAGED, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/idle_pulling.png");
    set_frame(4, 4, 192, 192, false, IDLE_PULLING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/idle_pushing.png");
    set_frame(4, 4, 192, 192, false, IDLE_PUSHING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/climbing.png");
    set_frame(5, 8, 136, 136, true, CLIMBING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    set_frame(5, 8, 136, 136, true, ENTERING_PORTAL, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    point = 0;
    is_the_game_ending = false;
    has_the_game_ended = false;
    was_last_direction_left = true;
    jump_clock.restart();
    end_clock.restart();
    hp = 3;
}
Vector2f Player::update()
{
    Vector2f old_position = sprite.getPosition();
    animate_player();
    move();
    if (get_current_state() == JUMPING && jump_clock.getElapsedTime().asSeconds() >= PLAYER_JUMP_SECONDS)
    {
        change_state(FALLING);
    }
    Vector2f new_position = sprite.getPosition();
    return new_position - old_position;
}
void Player::move()
{
    if (get_is_key_pressed(RIGHT))
    {
        if (get_current_state() != FALLING && get_current_state() != JUMPING && get_current_state() != DAMAGED)
        {
            change_state(WALKING);
        }
        Animated::move(PLAYER_SPEED, 0);
    }
    if (get_is_key_pressed(LEFT))
    {
        if (get_current_state() != FALLING && get_current_state() != JUMPING && get_current_state() != DAMAGED)
        {
            change_state(WALKING);
        }
        Animated::move(-PLAYER_SPEED, 0);
    }
    if (current_state == FALLING)
    {
        Animated::move(0, PLAYER_SPEED);
    }
    else if (get_current_state() == JUMPING)
    {
        Animated::move(0, -PLAYER_SPEED);
    }
    else
    {
        if (get_is_key_pressed(JUMP))
        {
            if (get_current_state() != JUMPING && get_current_state() != FALLING)
            {
                jump_clock.restart();
                change_state(JUMPING);
                Animated::scale_based_on_reflection(was_last_direction_left);
            }
        }
        else if (!get_is_key_pressed(RIGHT) && !get_is_key_pressed(LEFT) &&
                 !get_is_key_pressed(JUMP) && current_state != FALLING && current_state != DAMAGED &&
                 current_state != ENTERING_PORTAL)
        {
            change_state(IDLE);
        }
    }
    movement_clock.restart();
}
void Player::ghostify()
{
    Color sprite_color = sprite.getColor();
    if (sprite_color.a == 100)
    {
        sprite_color.a = 255;
        sprite.setColor(sprite_color);
    }
    else
    {
        sprite_color.a = 100;
        sprite.setColor(sprite_color);
    }
}
// accessors
int Player::get_hp()
{
    return hp;
}
int Player::get_points()
{
    return point;
}
bool Player::get_is_the_game_ending()
{
    return is_the_game_ending;
}
// modifiers
void Player::set_last_direction(bool left)
{
    was_last_direction_left = left;
}
void Player::add_point(int value)
{
    point += value;
}
void Player::animate_player()
{
    if (current_state == ENTERING_PORTAL)
    {
        set_current_frame_scale({get_current_frame_scale().x * 0.95f, get_current_frame_scale().y * 0.95f});
        set_is_key_pressed(RIGHT, false);
        set_is_key_pressed(LEFT, false);
        set_is_key_pressed(UP, false);
        set_is_key_pressed(DOWN, false);
        set_is_key_pressed(JUMP, false);
        Animated::animate(false);
        if (!has_the_game_ended)
        {
            end_clock.restart();
            has_the_game_ended = true;
        }
        if (end_clock.getElapsedTime().asSeconds() >= 2.4f)
        {
            is_the_game_ending = true;
        }
        return;
    }
    else
    {
        if (current_state == IDLE || current_state == FALLING ||
            current_state == JUMPING || current_state == DAMAGED)
        {
            Animated::scale_based_on_reflection(was_last_direction_left);
        }
        if (current_state == WALKING)
        {
            if (get_is_key_pressed(RIGHT))
            {
                Animated::animate(false);
                was_last_direction_left = false;
            }
            else if (get_is_key_pressed(LEFT))
            {
                Animated::animate(true);
                was_last_direction_left = true;
            }
        }
        else if (current_state == DAMAGED)
        {
            Animated::animate(was_last_direction_left);
        }
    }
}
void Player::decrease_hp()
{
    hp--;
    if (hp == 0)
    {
        is_the_game_ending = true;
    }
}

void Player::reset_points()
{
    point = 0;
}
