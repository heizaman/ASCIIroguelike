#include "GameSystem.h"
#include <conio.h>
#include <stdlib.h>
#include <cstdio>




GameSystem::GameSystem(string level1)
{
    _player.init(1, 100, 20, 20, 0);
    _level.load(level1, _player);
}

void GameSystem::playGame()
{
    bool isDone = false;

    while(!isDone) {
        _level.print();
        playerMove();
        if(checkVictory())
            isDone = true;
        _level.moveEnemies(_player);
        if(checkVictory())
            isDone = true;
    }
}

void GameSystem::playerMove() {
    char in;
    printf("Enter command to move (w/s/a/d), Press x for stats: ");

    in = getch();

    _level.movePlayer(in, _player);
}




bool GameSystem::checkVictory() {
    if(_level.getEnemySize() == 0) {
        _level.print();
        printf("You won!");
        system("PAUSE");

        return true;
    }

    return false;
}
