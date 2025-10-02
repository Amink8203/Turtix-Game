#include <iostream>
#include "Baby.hpp"
using namespace std;
Baby::Baby()
    : Animated(2)
{
  Texture texture;
  int rand_num = rand() % 2;
  if (rand_num == 0)
  {
    texture.loadFromFile("sprite/Frozen1.png");
    set_frame(5, 10, 152, 152, true, FROZEN, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/Moving_Baby1.png");
    set_frame(6, 16, 100, 100, true, MOVING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
  }
  else
  {
    texture.loadFromFile("sprite/Frozen2.png");
    set_frame(5, 10, 152, 152, true, FROZEN, ANIMATED_SPRITE_SCALE_FACTOR, texture);
    texture.loadFromFile("sprite/Moving_Baby2.png");
    set_frame(6, 16, 100, 100, true, MOVING, ANIMATED_SPRITE_SCALE_FACTOR, texture);
  }
  current_state = FROZEN;
  is_first_move = true;
  rotate = false;
  moving_state = -1;
  is_falling = false;
  baby_has_fallen = false;
}

void Baby::animate_baby()
{
  if (current_state == FROZEN)
  {
    Animated::animate(false);
    return;
  }
  else if (current_state == MOVING)
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
}
void Baby::update_move()
{
  if (moving_state == -1)
  {
    change_state(FROZEN);
    return;
  }

  else if (is_first_move)
  {
    movement_clock.restart();
    is_first_move = false;
    if (first_move_is_left)
    {
      if (rotate)
      {
        rotate = false;
        moving_state = RIGHT;
        change_state(MOVING);
        Animated::move(75, 0);
      }
      else
      {
        moving_state = LEFT;
        change_state(MOVING);
        Animated::move(-75, 0);
      }
    }
    else
    {
      if (rotate)
      {
        rotate = false;
        moving_state = LEFT;
        change_state(MOVING);
        Animated::move(-75, 0);
      }
      else
      {
        moving_state = RIGHT;
        change_state(MOVING);
        Animated::move(75, 0);
      }
    }
  }
  else if (is_falling)
  {
    if (moving_state == RIGHT)
    {
      change_state(MOVING);
      Animated::move(20, 75);
    }
    else
    {
      change_state(MOVING);
      Animated::move(-20, 75);
    }
  }
  else if (moving_state == LEFT && rotate)
  {
    rotate = false;
    moving_state = RIGHT;
    change_state(get_current_state());
    Animated::move(75, 0);
  }
  else if (moving_state == RIGHT && rotate)
  {
    rotate = false;
    moving_state = LEFT;
    change_state(get_current_state());
    Animated::move(-75, 0);
  }
  else if (moving_state == LEFT)
  {
    change_state(get_current_state());
    Animated::move(-75, 0);
  }
  else if (moving_state == RIGHT)
  {
    change_state(get_current_state());
    Animated::move(75, 0);
  }
  movement_clock.restart();
}

void Baby::update()
{
  animate_baby();
  update_move();
}
