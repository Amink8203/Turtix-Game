#ifndef _GAME_HPP
#define _GAME_HPP
#include "Player.hpp"
#include "Portal.hpp"
#include "Ground.hpp"
#include "Baby.hpp"
#include "Advanced_Enemy.hpp"
#include "Doublelife_Enemy.hpp"
#include "Animated.hpp"
#include "Point.hpp"
#include "Constants.hpp"
#include <fstream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

class Game
{
private:
    RenderWindow window;
    Event event;
    Player *player;
    void init_texts();
    vector<vector<Tile *>> tiles;
    Portal *portal;
    vector<Ground *> grounds;
    vector<Baby *> babies;
    vector<Point *> points;
    vector<AdvancedEnemy *> advanced_enemy;
    vector<DoublelifeEnemy *> doublelife_enemy;
    vector<Vector2f> advanced_enemy_pos;
    vector<Vector2f> doublelife_enemy_pos;
    vector<bool> baby_first_dir_left;
    vector<Vector2f> baby_pos;
    vector<Vector2f> points_pos;
    Texture ground_texture;
    Texture dirt_texture;
    Texture background_texture;
    Font font;
    Text stats_text;
    Text ending_text;
    Music music;
    Sprite background;
    vector<bool> did_doublelife_last_collide_end;
    vector<bool> did_advanced_last_collide_end;
    vector<bool> did_baby_last_collide_end;
    vector<bool> does_doublelife_collide;
    vector<bool> does_advanced_collide;
    vector<bool> does_baby_collide;
    bool has_Animateds_spawned;
    bool player_has_fallen;
    bool is_player_ghost;
    Clock ghost;
    // functions
    // void add_baby(float _x, float _y, int input_mspf, Vector2f _sprite_scale_factor);
    void init_baby_dir();
    void update_babies();
    void update_advanced_enemies();
    void update_doublelife_enemies();
    virtual void update();
    virtual void render();
    void delete_everything();
    void damage_player();
    vector<vector<Tile *>> make_terrain(float _tile_scale_factor, Texture &ground_texture);
    // update functions
    void key_pressed();
    void key_released();
    void update_points();
    void update_gui();
    void detect_collision();
    bool does_it_collide_with_grounds(Animated *collided,
                                      moving_directions collided_relative_pos);
    int anim_mspf;
    Vector2f scale_factor;

public:
    Game();
    bool run();
    // baraye constructor ha lazem bood!
};
#endif