#include <iostream>
#include <conio.h>  // For getch()

using namespace std;

#include "GameSystem.h"




//ASCII Dungeon Game

// ##########
// #.......S#
// #....S...#
// #........#
// #...@...S#
// ##########

//@ is player
//S is snake
//  is air
//# is wall

//@ moves in   but can't move through # and is battled by S if comes across any




int main()
{
    GameSystem gamesystem("level1.txt");
    gamesystem.playGame();

    return 0;
}
