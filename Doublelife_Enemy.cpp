#include "Doublelife_Enemy.hpp"

DoublelifeEnemy::DoublelifeEnemy()
    : Animated(2)
{
    Texture texture;
    texture.loadFromFile("sprite/Doublelife_Enemy1.png");
    set_frame(6, 3, 115, 115, false, TWO_LIVES, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/Doublelife_Enemy2.png");
    set_frame(5, 5, 112, 112, false, ONE_LIFE, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    current_state = TWO_LIVES;
    moving_state = RIGHT;
    first_collision = false;
    rotate = false;
    temp = true;
    clock.restart();
}

Vector2f DoublelifeEnemy::get_down()
{
    Vector2f temp;
    if (moving_state == LEFT)
    {
        temp.x = sprite.getGlobalBounds().left-1.f;
        temp.y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height+1.f;
        return temp;
    }
    else
    {
        temp.x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width+1.f;
        temp.y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height+1.f;
        return temp;
    }
}

void DoublelifeEnemy::animate_double()
{
    if (moving_state == LEFT)
    {
        Animated::animate(true);
        return;
    }
    else
    {
        Animated::animate(false);
        return;
    }
}
void DoublelifeEnemy::update_move()
{
    if (first_collision && temp)
    {
        temp = false;
        change_state(ONE_LIFE);
    }
    if (rotate && moving_state == LEFT)
    {
        rotate = false;
        moving_state = RIGHT;
        change_state(get_current_state());
        Animated::move(25, 0);
    }
    else if (rotate && moving_state == RIGHT)
    {
        rotate = false;
        moving_state = LEFT;
        change_state(get_current_state());
        Animated::move(-25, 0);
    }
    if (moving_state == LEFT)
    {
        change_state(get_current_state());
        Animated::move(-25, 0);
    }
    if (moving_state == RIGHT)
    {
        change_state(get_current_state());
        Animated::move(25, 0);
    }
    movement_clock.restart();
}

void DoublelifeEnemy::update()
{
    animate_double();
    update_move();
}