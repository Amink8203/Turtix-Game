all: turtix.out

turtix.out: Point.o Portal.o Ground.o Tile.o Doublelife_Enemy.o Advanced_Enemy.o Baby.o Player.o Animated.o Game.o main.o
	g++ Point.o Portal.o Ground.o Tile.o Doublelife_Enemy.o Advanced_Enemy.o Baby.o Player.o Animated.o Game.o main.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o turtix.out

main.o: main.cpp Game.hpp
	g++ -c main.cpp

Game.o : Game.cpp Doublelife_Enemy.hpp Advanced_Enemy.o Player.hpp Portal.hpp Ground.hpp Point.hpp Constants.hpp Game.hpp
	g++ -c Game.cpp

Animated.o: Animated.cpp Constants.hpp Animated.hpp
	g++ -c Animated.cpp

Player.o : Player.cpp Animated.hpp Constants.hpp Player.hpp
	g++ -c Player.cpp
	
Doublelife_Enemy.o : Doublelife_Enemy.cpp Animated.hpp Constants.hpp Doublelife_Enemy.hpp
	g++ -c Doublelife_Enemy.cpp

Advanced_Enemy.o : Advanced_Enemy.cpp Animated.hpp Constants.hpp Doublelife_Enemy.hpp
	g++ -c Advanced_Enemy.cpp

Baby.o : Baby.cpp Animated.hpp Constants.hpp Baby.hpp
	g++ -c Baby.cpp

Tile.o : Tile.cpp Constants.hpp Tile.hpp
	g++ -c Tile.cpp

Portal.o : Portal.cpp Tile.hpp Constants.hpp Portal.hpp
	g++ -c Portal.cpp

Ground.o : Ground.cpp Tile.hpp Constants.hpp Ground.hpp
	g++ -c Ground.cpp

Point.o: Point.cpp Animated.hpp Constants.hpp Point.hpp
	g++ -c Point.cpp

clean :
	rm *.o turtix.out
