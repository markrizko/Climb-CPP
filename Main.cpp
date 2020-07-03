/*
Hack For Humanity 2020 Project by
Mark Rizko, Cameron Burdsall, and Fernando Camou

Climb: A 2 Player Card game written by Mark Rizko written using
SDL2 in C++ in Visual Studio.
*/

#include "Game.h"


int main(int argc, char * argv[])
{
    srand(time(NULL));
	Game game;
	game.runGame();

	return 0;
}