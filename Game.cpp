#include "Game.hpp"
#include <iostream>
using namespace std;
Game::Game()
{
    window.create(VideoMode().getDesktopMode(), "Turtix", Style::Default);
    ground_texture.loadFromFile("sprite/ground.png");
    background_texture.loadFromFile("sprite/background.jpg");
    background.setTexture(background_texture);
    background.setScale(0.1f, 0.1f);
    music.openFromFile("music.ogg");
    music.play();
    music.setLoop(true);
    baby_first_dir_left.push_back(false);
    baby_first_dir_left.push_back(true);
    baby_first_dir_left.push_back(true);
    tiles = make_terrain(TILE_SPRITE_SCALE_FACTOR, ground_texture);
    View window_view = window.getView();
    window_view.zoom(0.2f);
    window.setView(window_view);
    anim_mspf = ANIMATION_MILLISECONDS_PER_FRAME;
    scale_factor = ANIMATED_SPRITE_SCALE_FACTOR;
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    player = new Player();
    player_has_fallen = false;
    has_Animateds_spawned = false;
    is_player_ghost = false;
    init_texts();
    ghost.restart();
}
bool Game::run()
{
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (player->get_is_the_game_ending() && event.key.code == Keyboard::Space)
                {
                    delete_everything();
                    return false;
                }
                key_pressed();
            }
            else if (event.type == Event::KeyReleased)
            {
                key_released();
            }
            else if (event.type == Event::Closed)
            {
                delete_everything();
                return true;
            }
        }
        window.clear();
        render();
        window.display();
        if (!player->get_is_the_game_ending())
        {
            update();
        }
        if (player->get_is_the_game_ending())
        {
            if (player->get_hp() == 0)
            {
                ending_text.setFillColor(Color::Red);
                ending_text.setString("GAME OVER!");
                ending_text.setCharacterSize(200);
            }
            else
            {
                ending_text.setFillColor(Color::Green);
                ending_text.setString("YOU WON!");
                ending_text.setCharacterSize(200);
            }
        }
    }
    return true;
}

void Game::init_texts()
{
    font.loadFromFile("font.ttf");
    stats_text.setFont(font);
    stats_text.setCharacterSize(100);
    stats_text.setScale({0.1f, 0.1f});
    stats_text.setFillColor(Color::White);
    stats_text.setString("Points: 0");

    ending_text.setFont(font);
    ending_text.setCharacterSize(0);
    ending_text.setScale({0.1f, 0.1f});
}

void Game::init_baby_dir()
{
    for (int i = 0; i < babies.size(); i++)
    {
        babies[i]->first_move_is_left = baby_first_dir_left[i];
    }
}
void Game::update_babies()
{
    for (int i = 0; i < babies.size(); i++)
    {
        babies[i]->update();
    }
}
void Game::update()
{
    // havaset be jaye in bashe ke age eshtebah bood avaz koni!
    detect_collision();
    update_babies();
    update_points();
    update_advanced_enemies();
    update_doublelife_enemies();
    update_gui();
    if (ghost.getElapsedTime().asSeconds() > 3.f && is_player_ghost)
    {
        player->ghostify();
        player->change_state(WALKING);
        is_player_ghost = false;
    }
}
void Game::render()
{
    window.draw(background);
    for (auto &row_tile : tiles)
    {
        for (auto &tile : row_tile)
        {
            if (tile != NULL)
            {
                tile->render(&window);
            }
        }
    }
    if (has_Animateds_spawned == false)
    {
        for (int i = 0; i < babies.size(); i++)
        {
            babies[i]->first_move_is_left = baby_first_dir_left[i];
            babies[i]->spawn(baby_pos[i]);
        }
        for (int i = 0; i < doublelife_enemy.size(); i++)
        {
            doublelife_enemy[i]->spawn(doublelife_enemy_pos[i]);
        }
        for (int i = 0; i < advanced_enemy.size(); i++)
        {
            advanced_enemy[i]->spawn(advanced_enemy_pos[i]);
        }
        for (int i = 0; i < points.size(); i++)
        {
            points[i]->spawn(points_pos[i]);
        }
        VideoMode temp_video;
        Vector2f temp_pos = portal->get_position();
        temp_pos.y -= temp_video.getDesktopMode().height / 50;
        player->spawn(temp_pos);
        player->reset_points();
        View window_view = window.getView();
        window_view.setCenter(portal->get_position());
        temp_pos.x = portal->get_position().x - temp_video.getDesktopMode().width / 10;
        temp_pos.y = portal->get_position().y - temp_video.getDesktopMode().height / 10;
        background.setPosition(temp_pos);
        temp_pos.x += temp_video.getDesktopMode().width / 100;
        temp_pos.y += temp_video.getDesktopMode().height / 100;
        stats_text.setPosition(temp_pos);
        temp_pos.x += temp_video.getDesktopMode().width / 17;
        temp_pos.y += temp_video.getDesktopMode().height / 25;
        ending_text.setPosition(temp_pos);
        window.setView(window_view);
        has_Animateds_spawned = true;
    }
    for (int i = 0; i < babies.size(); i++)
    {
        babies[i]->render(&window);
    }
    for (int i = 0; i < doublelife_enemy.size(); i++)
    {
        doublelife_enemy[i]->render(&window);
    }
    for (int i = 0; i < advanced_enemy.size(); i++)
    {
        advanced_enemy[i]->render(&window);
    }
    for (int i = 0; i < points.size(); i++)
    {
        points[i]->render(&window);
    }
    player->render(&window);
    window.draw(stats_text);
    window.draw(ending_text);
}
void Game::delete_everything()
{
    for (auto &row_tile : tiles)
    {
        for (auto &tile : row_tile)
        {
            if (tile != NULL)
            {
                delete tile;
            }
        }
    }
    delete player;
    for (int i = 0; i < babies.size(); i++)
    {
        delete babies[i];
    }
    for (int i = 0; i < doublelife_enemy.size(); i++)
    {
        delete doublelife_enemy[i];
    }
    for (int i = 0; i < advanced_enemy.size(); i++)
    {
        delete advanced_enemy[i];
    }
    for (int i = 0; i < points.size(); i++)
    {
        delete points[i];
    }
    window.close();
}
void Game::damage_player()
{
    ghost.restart();
    player->decrease_hp();
    player->change_state(DAMAGED);
    if (!is_player_ghost)
    {
        player->ghostify();
        is_player_ghost = true;
    }
}
vector<vector<Tile *>> Game::make_terrain(float _tile_scale_factor, Texture &ground_texture)
{
    vector<vector<Tile *>> terrain;
    string str_row_tile;
    ifstream map("map.txt");
    vector<Tile *> temp_row_tile;
    while (getline(map, str_row_tile))
    {
        for (int i = 0; i < str_row_tile.size(); i++)
        {
            switch (str_row_tile[i])
            {
            case '.':
                grounds.push_back(new Ground(ground_texture, i, terrain.size() - 1));
                temp_row_tile.push_back(grounds[grounds.size() - 1]);
                break;
            case '$':
                portal = new Portal(i, terrain.size() - 1);
                temp_row_tile.push_back(portal);
                break;
            case 'O':
            {
                Portal temp_portal(i, terrain.size() - 1);
                baby_pos.push_back(temp_portal.get_position());
                Baby *baby = new Baby();
                babies.push_back(baby);
                did_baby_last_collide_end.push_back(true);
                does_baby_collide.push_back(false);
            }
            break;
            case 'E':
            {
                Portal temp_portal(i, terrain.size() - 1);
                doublelife_enemy_pos.push_back(temp_portal.get_position());
                DoublelifeEnemy *d_enemy = new DoublelifeEnemy();
                doublelife_enemy.push_back(d_enemy);
                did_doublelife_last_collide_end.push_back(true);
                does_doublelife_collide.push_back(false);
            }
            break;
            case 'M':
            {
                Portal temp_portal(i, terrain.size() - 1);
                advanced_enemy_pos.push_back(temp_portal.get_position());
                AdvancedEnemy *a_enemy = new AdvancedEnemy();
                advanced_enemy.push_back(a_enemy);
                did_advanced_last_collide_end.push_back(true);
                does_advanced_collide.push_back(false);
            }
            break;
            case '^':
            {
                Portal temp_portal(i, terrain.size() - 1);
                points_pos.push_back(temp_portal.get_position());
                Point *new_point = new Point(DIAMOND);
                points.push_back(new_point);
            }
            break;
            case '*':
            {
                Portal temp_portal(i, terrain.size() - 1);
                points_pos.push_back(temp_portal.get_position());
                Point *new_point = new Point(STAR);
                points.push_back(new_point);
            }
            break;

            default:
                temp_row_tile.push_back(NULL);
                break;
            }
        }
        terrain.push_back(temp_row_tile);
        temp_row_tile.clear();
        str_row_tile.clear();
    }
    map.close();
    return terrain;
}
void Game::key_pressed()
{
    /*     if (event.key.code == Keyboard::S)
        {
            player->set_is_key_pressed(DOWN, true);
            player->set_is_key_pressed(UP, false);
        }
        else if (event.key.code == Keyboard::W)
        {
            player->set_is_key_pressed(UP, true);
            player->set_is_key_pressed(DOWN, false);
        } */
    if (event.key.code == Keyboard::D)
    {
        player->set_is_key_pressed(RIGHT, true);
        player->set_is_key_pressed(LEFT, false);
    }
    else if (event.key.code == Keyboard::A)
    {
        player->set_is_key_pressed(LEFT, true);
        player->set_is_key_pressed(RIGHT, false);
    }
    else if (event.key.code == Keyboard::W)
    {
        player->set_is_key_pressed(JUMP, true);
    }
}
void Game::key_released()
{
    /*     if (event.key.code == Keyboard::S)
        {
            player->set_is_key_pressed(DOWN, false);
        }
        else if (event.key.code == Keyboard::W)
        {
            player->set_is_key_pressed(UP, false);
        } */
    if (event.key.code == Keyboard::D)
    {
        player->set_is_key_pressed(RIGHT, false);
    }
    else if (event.key.code == Keyboard::A)
    {
        player->set_is_key_pressed(LEFT, false);
    }
    else if (event.key.code == Keyboard::W)
    {
        player->set_is_key_pressed(JUMP, false);
    }
}
void Game::update_points()
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i]->update();
    }
}
void Game::update_doublelife_enemies()
{
    for (int i = 0; i < doublelife_enemy.size(); i++)
    {
        doublelife_enemy[i]->update();
    }
}
void Game::update_advanced_enemies()
{
    for (int i = 0; i < advanced_enemy.size(); i++)
    {
        advanced_enemy[i]->update();
    }
}
void Game::update_gui()
{
    stringstream ss;
    ss << "Points: " << player->get_points() << endl;
    ss << "HP: " << player->get_hp();
    stats_text.setString(ss.str());
    Vector2f view_move_vector = player->update();
    stats_text.move(view_move_vector);
    ending_text.move(view_move_vector);
    View window_view = window.getView();
    window_view.move(view_move_vector);
    window.setView(window_view);
    background.move(view_move_vector);
}
void Game::detect_collision()
{
    if (player->get_current_state() != JUMPING)
    {
        if (!does_it_collide_with_grounds(player, UP))
        {
            player->change_state(FALLING);
            player_has_fallen = true;
        }
        else if (player_has_fallen == true)
        {
            player->change_state(IDLE);
            player_has_fallen = false;
        }
    }
    else
    {
        if (does_it_collide_with_grounds(player, DOWN))
        {
            player->change_state(FALLING);
            player_has_fallen = true;
        }
    }
    if (player->get_is_key_pressed(LEFT))
    {
        if (does_it_collide_with_grounds(player, RIGHT))
        {
            player->set_is_key_pressed(LEFT, false);
        }
        player->set_last_direction(true);
    }
    if (player->get_is_key_pressed(RIGHT))
    {
        if (does_it_collide_with_grounds(player, LEFT))
        {
            player->set_is_key_pressed(RIGHT, false);
        }
        player->set_last_direction(false);
    }
    FloatRect player_rect = player->get_global_bounds();
    if (portal->get_is_portal_open() && portal->does_it_collide(player_rect))
    {
        player->change_state(ENTERING_PORTAL);
    }
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i]->does_it_collide(player_rect))
        {
            points[i]->move(1000, 1000);
            player->add_point(points[i]->get_point());
        }
    }
    for (int j = 0; j < babies.size(); j++)
    {
        if (!does_it_collide_with_grounds(babies[j], UP))
        {
            babies[j]->is_falling = true;
        }
        else
        {
            babies[j]->is_falling = false;
        }
        if ((does_it_collide_with_grounds(babies[j], RIGHT) ||
             does_it_collide_with_grounds(babies[j], LEFT)) &&
            !babies[j]->is_falling)
        {
            if (did_baby_last_collide_end[j])
            {
                does_baby_collide[j] = true;
                did_baby_last_collide_end[j] = false;
            }
        }
        else
        {
            did_baby_last_collide_end[j] = true;
        }
        if (does_baby_collide[j] == true)
        {
            babies[j]->rotate = true;
            does_baby_collide[j] = false;
        }
    }
    for (int i = 0; i < babies.size(); i++)
    {
        FloatRect baby_rect = babies[i]->get_global_bounds();
        if (player->get_current_state() == FALLING && babies[i]->does_it_collide(player_rect) && babies[i]->get_current_state() == FROZEN)
        {
            if (babies[i]->first_move_is_left)
            {
                babies[i]->moving_state = LEFT;
            }
            else
            {
                babies[i]->moving_state = RIGHT;
            }
        }
        if (portal->does_it_collide(baby_rect))
        {
            delete babies[i];
            babies.erase(babies.begin() + i);
            i = -1;
        }
        if (babies.size() == 0)
        {
            portal->change_portal();
        }
    }
    for (int j = 0; j < doublelife_enemy.size(); j++)
    {
        int i;
        for (i = 0; i < grounds.size(); i++)
        {
            if (grounds[i]->does_it_contain(doublelife_enemy[j]->get_down()))
            {
                break;
            }
        }
        if (i == grounds.size() ||
            does_it_collide_with_grounds(doublelife_enemy[j], RIGHT) ||
            does_it_collide_with_grounds(doublelife_enemy[j], LEFT))
        {
            if (did_doublelife_last_collide_end[j])
            {
                does_doublelife_collide[j] = true;
                did_doublelife_last_collide_end[j] = false;
            }
        }
        else
        {
            did_doublelife_last_collide_end[j] = true;
        }
        if (does_doublelife_collide[j] == true)
        {
            doublelife_enemy[j]->rotate = true;
            does_doublelife_collide[j] = false;
        }
    }

    for (int j = 0; j < advanced_enemy.size(); j++)
    {
        int i;
        for (i = 0; i < grounds.size(); i++)
        {
            if (grounds[i]->does_it_contain(advanced_enemy[j]->get_down()))
            {
                break;
            }
        }
        if (i == grounds.size() ||
            does_it_collide_with_grounds(advanced_enemy[j], RIGHT) ||
            does_it_collide_with_grounds(advanced_enemy[j], LEFT))
        {
            if (did_advanced_last_collide_end[j])
            {
                does_advanced_collide[j] = true;
                did_advanced_last_collide_end[j] = false;
            }
        }
        else
        {
            did_advanced_last_collide_end[j] = true;
        }
        if (does_advanced_collide[j] == true)
        {
            advanced_enemy[j]->rotate = true;
            does_advanced_collide[j] = false;
        }
    }
    for (int i = 0; i < doublelife_enemy.size(); i++)
    {
        if (player->get_current_state() == FALLING && doublelife_enemy[i]->does_it_collide(player_rect) && ghost.getElapsedTime().asSeconds() > 3.f)
        {
            if (doublelife_enemy[i]->first_collision == false)
            {
                doublelife_enemy[i]->clock.restart();
                doublelife_enemy[i]->first_collision = true;
            }
            else if (doublelife_enemy[i]->clock.getElapsedTime().asSeconds() > 2.f &&
                     ghost.getElapsedTime().asSeconds() > 3.f)
            {
                delete doublelife_enemy[i];
                doublelife_enemy.erase(doublelife_enemy.begin() + i);
                i = -1;
            }
        }
        // ghost:halate rooh
        // .clock:namordane enemy darja!
        else if (player->get_current_state() != FALLING &&
                 doublelife_enemy[i]->does_it_collide(player_rect) &&
                 doublelife_enemy[i]->clock.getElapsedTime().asSeconds() > 1.f &&
                 ghost.getElapsedTime().asSeconds() > 3.f)
        {
            damage_player();
        }
    }

    for (int i = 0; i < advanced_enemy.size(); i++)
    {
        if (player->get_current_state() == FALLING &&
            advanced_enemy[i]->does_it_collide(player_rect) &&
            ghost.getElapsedTime().asSeconds() > 3.f)
        {
            // halate unbeatable.
            if (advanced_enemy[i]->is_unbeatable == true && advanced_enemy[i]->player_clock.getElapsedTime().asSeconds() > 2.f && ghost.getElapsedTime().asSeconds() > 3.f)
            {
                advanced_enemy[i]->player_clock.restart();
                damage_player();
            }
            // halate mamooli.
            if (advanced_enemy[i]->is_unbeatable == false && advanced_enemy[i]->player_clock.getElapsedTime().asSeconds() > 2.f && ghost.getElapsedTime().asSeconds() > 3.f)
            {
                advanced_enemy[i]->player_clock.restart();
                delete advanced_enemy[i];
                advanced_enemy.erase(advanced_enemy.begin() + i);
                i = -1;
            }
        }
        else if (player->get_current_state() != FALLING &&
                 advanced_enemy[i]->does_it_collide(player_rect) &&
                 advanced_enemy[i]->player_clock.getElapsedTime().asSeconds() > 1.f &&
                 ghost.getElapsedTime().asSeconds() > 3.f)
        {
            damage_player();
            // cout << player->get_hp();
            // cout << player->get_hp();
        }
    }
}
bool Game::does_it_collide_with_grounds(Animated *collided,
                                        moving_directions collided_relative_pos)
{
    FloatRect collided_rect = collided->get_global_bounds();
    for (int i = 0; i < grounds.size(); i++)
    {
        if (grounds[i]->does_it_collide(collided_rect))
        {
            switch (collided_relative_pos)
            {
            case UP:
                if (grounds[i]->get_global_bounds().top <=
                        (collided->get_global_bounds().top + collided->get_global_bounds().height) &&
                    grounds[i]->get_global_bounds().top >=
                        collided->get_global_bounds().top &&
                    grounds[i]->get_global_bounds().left + grounds[i]->get_global_bounds().width - COLLISION_PRECISION >=
                        collided->get_global_bounds().left &&
                    grounds[i]->get_global_bounds().left <=
                        collided->get_global_bounds().left + collided->get_global_bounds().width - COLLISION_PRECISION)
                {
                    return true;
                }
                break;
            case DOWN:
                if (grounds[i]->get_global_bounds().top + grounds[i]->get_global_bounds().height >=
                        collided->get_global_bounds().top &&
                    grounds[i]->get_global_bounds().top + grounds[i]->get_global_bounds().height <=
                        collided->get_global_bounds().top + collided->get_global_bounds().height &&
                    grounds[i]->get_global_bounds().left + grounds[i]->get_global_bounds().width - COLLISION_PRECISION >=
                        collided->get_global_bounds().left &&
                    grounds[i]->get_global_bounds().left <=
                        collided->get_global_bounds().left + collided->get_global_bounds().width - COLLISION_PRECISION)
                {
                    return true;
                }
                break;
            case RIGHT:
                if (grounds[i]->get_global_bounds().left + grounds[i]->get_global_bounds().width >=
                        collided->get_global_bounds().left &&
                    grounds[i]->get_global_bounds().left + grounds[i]->get_global_bounds().width <=
                        collided->get_global_bounds().left + collided->get_global_bounds().width &&
                    grounds[i]->get_global_bounds().top <=
                        (collided->get_global_bounds().top + collided->get_global_bounds().height - COLLISION_PRECISION) &&
                    (grounds[i]->get_global_bounds().top + grounds[i]->get_global_bounds().height - COLLISION_PRECISION > collided->get_global_bounds().top))
                {
                    return true;
                }
                break;
            case LEFT:
                if (grounds[i]->get_global_bounds().left <=
                        collided->get_global_bounds().left + collided->get_global_bounds().width &&
                    grounds[i]->get_global_bounds().left >=
                        collided->get_global_bounds().left &&
                    grounds[i]->get_global_bounds().top <=
                        (collided->get_global_bounds().top + collided->get_global_bounds().height - COLLISION_PRECISION) &&
                    (grounds[i]->get_global_bounds().top + grounds[i]->get_global_bounds().height - COLLISION_PRECISION > collided->get_global_bounds().top))
                {
                    return true;
                }
                break;

            default:
                break;
            }
        }
    }
    return false;
}
