#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "Player.h"
#include "Enemy.h"

using namespace std;




//A class for the level - store, print, process
class Level
{
    public:
        Level();

        //Loads the level from a file, Sets the player position, Populates the enemies vector
        void load(string filename, Player &player);

        //Prints the level
        void print();

        //Checks the move and moves the player if possible
        void movePlayer(char move, Player &player);

        //Moves the enemies
        void moveEnemies(Player &player);

        //Return size of enemy vector
        int getEnemySize();

    private:
        void processPlayerMove(Player &player, int tx, int ty);

        void battleEnemy(Player &player, int tx, int ty);
        void battlePlayer(Player &player, int tx, int ty);

        void processEnemyMove(Player &player, int i, int tx, int ty);

        void printStats(Player &player);

        vector<string> _leveldata;
        vector<Enemy> _enemies;
};

#endif // LEVEL_H
