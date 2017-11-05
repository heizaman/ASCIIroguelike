#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <string>

using namespace std;

#include "Player.h"
#include "Level.h"




//A class that holds together our game
class GameSystem
{
    public:
        //Loads our level from a file
        GameSystem(string level1);

        void playGame();

    protected:

    private:
        //Has the loaded level, player, enemies
        Player _player;
        Level _level;

        void playerMove();

        bool checkVictory();
};

#endif // GAMESYSTEM_H
