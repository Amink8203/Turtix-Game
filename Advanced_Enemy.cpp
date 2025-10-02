#include "Advanced_Enemy.hpp"

AdvancedEnemy::AdvancedEnemy()
    : Animated(2)
{
    Texture texture;
    texture.loadFromFile("sprite/Advanced_Enemy1.png");
    set_frame(6, 6, 85, 89, true, ORDINARY, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/Advanced_Enemy2.png");
    set_frame(6, 6, 85, 89, true, UNBEATABLE, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    player_clock.restart();
    enemy_clock.restart();
    rotate = false;
    current_state = ORDINARY;
    moving_state = RIGHT;
    is_unbeatable = false;

}

Vector2f AdvancedEnemy::get_down()
{
    Vector2f temp;
    if (moving_state == LEFT)
    {
        temp.x = sprite.getGlobalBounds().left-1.f*85/115;
        temp.y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height+1.f*89/115;
        return temp;
    }
    else
    {
        temp.x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width+1.f*85/115;
        temp.y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height+1.f*89/115;
        return temp;
    }
}

void AdvancedEnemy::animate_advanced()
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

void AdvancedEnemy::update_move()
{
    if(current_state == ORDINARY && enemy_clock.getElapsedTime().asSeconds()>6)
    {
        enemy_clock.restart();
        is_unbeatable = true;
        change_state(UNBEATABLE);
    }
    if(current_state == UNBEATABLE && enemy_clock.getElapsedTime().asSeconds()>6)
    {
        enemy_clock.restart();
        is_unbeatable = false;
        change_state(ORDINARY);
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
    else if (moving_state == LEFT)
    {
        change_state(get_current_state());
        Animated::move(-25, 0);
    }
    else if (moving_state == RIGHT)
    {
        change_state(get_current_state());
        Animated::move(25, 0);
    }
    movement_clock.restart();

}

void AdvancedEnemy::update()
{
    animate_advanced();
    update_move();
}
