/*
ORIGINALLY Hack For Humanity 2020 Project by
Mark Rizko, Cameron Burdsall, and Fernando Camou

Took the project individually beyond the Hackathon in order to finish
 implementing the logic for the card game. 
Climb: A 2 Player Card game written by Mark Rizko written in C++.

*/

#include "Game.h"


int main(int argc, char * argv[])
{
    srand(time(NULL));
    bool pflag = true;
	Game game;
	while(pflag){
	    game.welcomeScreen();
	    game.runGame();
	    if (game.pa){
	        game = Game(); // reset game object if playing again
	    }
	    else{
	        pflag = false;
	    }
	}
	return 0;
}