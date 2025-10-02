#include "Game.hpp"
#include <iostream>
#include <ctime>
int main()
{
    srand(static_cast<unsigned int>(time(0)));
    bool quit = false;
    while (!quit)
    {
        Game *game = new Game();
        quit = game->run();
        delete game;
    }
    return 0;
}
/*
g++ -c main.cpp && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app
*/