#include "Animated.hpp"
Animated::Animated(int number_of_current_states)
{
    frames.resize(number_of_current_states);
    animation_mspf = ANIMATION_MILLISECONDS_PER_FRAME;
    animation_clock.restart();
    movement_clock.restart();
    current_state = -1;
    for (auto &key : is_key_pressed)
    {
        key = false;
    }
    has_state_changed = true;
    init_animation();
}
void Animated::spawn(Vector2f spawn_pos)
{
    has_state_changed = true;
    init_animation();
    Vector2f origin_spawn_pos = {spawn_pos.x - sprite.getTextureRect().width *
                                                   frames[current_state].sprite_scale.x / 2,
                                 spawn_pos.y - sprite.getTextureRect().height *
                                                   frames[current_state].sprite_scale.y};
    sprite.setPosition(origin_spawn_pos);
}
void Animated::render(RenderTarget *window)
{
    window->draw(sprite);
}
void Animated::move(float x, float y)
{
    Time elapsed_time = movement_clock.getElapsedTime();
    sprite.move(x * elapsed_time.asSeconds(), y * elapsed_time.asSeconds());
    // inja clock restart mishod
}
bool Animated::get_is_key_pressed(moving_directions dir)
{
    return is_key_pressed[dir];
}
FloatRect Animated::get_global_bounds()
{
    return sprite.getGlobalBounds();
}
void Animated::set_is_key_pressed(moving_directions dir, bool new_value)
{
    if (is_key_pressed[dir] != new_value)
    {
        is_key_pressed[dir] = new_value;
        movement_clock.restart();
    }
}
Vector2f Animated::get_current_frame_scale()
{
    return frames[current_state].sprite_scale;
}
void Animated::set_current_frame_scale(Vector2f new_scale)
{
    frames[current_state].sprite_scale = new_scale;
}
void Animated::set_frame(int _row_frames, int _total_frames, int _width, int _height,
                         bool _does_aniamtion_loop, short int _state, Vector2f _scale, Texture _texture)
{
    frames[_state].texture = _texture;
    frames[_state].row_frames = _row_frames;
    frames[_state].total_frames = _total_frames;
    frames[_state].width = _width;
    frames[_state].height = _height;
    frames[_state].does_animation_loop = _does_aniamtion_loop;
    frames[_state].sprite_scale.x = ((_scale.x / _width) * SPRITE_BASE_LENGTH.x);
    frames[_state].sprite_scale.y = ((_scale.y / _height) * SPRITE_BASE_LENGTH.y);
}
void Animated::init_animation()
{
    if (has_state_changed)
    {
        has_state_changed = false;
        frame_rect.width = frames[current_state].width;
        frame_rect.height = frames[current_state].height;
        frame_rect.left = frame_rect.top = 0;
        frame_counter = 0;
        sprite.setScale(frames[current_state].sprite_scale.x, frames[current_state].sprite_scale.y);
        sprite.setTextureRect(frame_rect);
        animation_direction = FORWARD;
        sprite.setTexture(frames[current_state].texture);
    }
}
void Animated::animate(bool shall_reflect)
{
    int number_of_frames_in_a_row = frames[current_state].row_frames;
    int total_number_of_frames = frames[current_state].total_frames;
    scale_based_on_reflection(shall_reflect);
    if (animation_clock.getElapsedTime().asMilliseconds() >= animation_mspf || has_state_changed)
    {
        frame_rect.left = (frame_counter % number_of_frames_in_a_row) * frame_rect.width;
        frame_rect.top = (frame_counter / number_of_frames_in_a_row) * frame_rect.height;
        if (frame_counter == 0)
        {
            frame_rect.left = 0;
            frame_rect.top = 0;
        }
        frame_rect.left = (frame_counter % number_of_frames_in_a_row) * frame_rect.width;
        frame_rect.top = (frame_counter / number_of_frames_in_a_row) * frame_rect.height;
        sprite.setTextureRect(frame_rect);
        frame_counter += animation_direction;
        if (frame_counter == total_number_of_frames || frame_counter == -1)
        {
            if (frames[current_state].does_animation_loop)
            {
                frame_counter = 0;
            }
            else
            {
                change_direction();
                frame_counter += 2 * animation_direction;
            }
        }
        animation_clock.restart();
        has_state_changed = false;
    }
}
void Animated::change_state(short int new_state)
{
    if (current_state != new_state)
    {
        current_state = new_state;
        has_state_changed = true;
        init_animation();
    }
}
void Animated::scale_based_on_reflection(bool shall_reflect)
{
    if (shall_reflect && frames[current_state].sprite_scale.x < 0)
    {
        frames[current_state].sprite_scale.x *= -1;
        sprite.setOrigin(0, 0);
    }
    else if (!shall_reflect && frames[current_state].sprite_scale.x > 0)
    {
        frames[current_state].sprite_scale.x *= -1;
        sprite.setOrigin(sprite.getGlobalBounds().width / (-frames[current_state].sprite_scale.x), 0);
    }
    sprite.setScale(frames[current_state].sprite_scale.x, frames[current_state].sprite_scale.y);
}
void Animated::change_direction()
{
    if (animation_direction == FORWARD)
    {
        animation_direction = BACKWARD;
        return;
    }
    animation_direction = FORWARD;
}
short int Animated::get_frame_counter()
{
    return frame_counter;
}
short int Animated::get_current_state()
{
    return current_state;
}
Vector2f Animated::get_position()
{
    Vector2f pos = sprite.getPosition();
    pos.x += sprite.getTextureRect().width / 2;
    pos.y += sprite.getTextureRect().height / 2;
    return pos;
}
bool Animated::does_it_collide(FloatRect &collided)
{
    return sprite.getGlobalBounds().intersects(collided);
}