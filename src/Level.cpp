#include "Level.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdio>




Level::Level()
{
    //ctor
}




void Level::load(string filename, Player &player)
{
    //Loads the level

    ifstream file;

    file.open(filename);
    if(file.fail()) {
        perror(filename.c_str());
        system("PAUSE");
        exit(1);
    }

    string line;

    while(getline(file, line)) {
        _leveldata.push_back(line);
    }

    file.close();

    //Processes the level
    for(int i=0; i<_leveldata.size(); i++) {
        string s = _leveldata[i];
        for(int j=0; j<s.size(); j++) {
            char c = s[j];

            switch(c) {
            case '@':
                player.setPosition(j, i);
                break;
            case 's':
            case 'S':
                _enemies.push_back(Enemy("Snake", 'S', 1, 1, 5, 1, 50, 5, j, i));
                break;
            case 'g':
            case 'G':
                _enemies.push_back(Enemy("Goblin", 'G', 5, 10, 30, 5, 150, 8, j, i));
                break;
            case 'd':
            case 'D':
                _enemies.push_back(Enemy("Dragon", 'D', 10, 100, 100, 50, 500, 10, j, i));
                break;
            }
        }
    }
}




void Level::print()
{
    cout << string(30, '\n');

    for(int i=0; i<_leveldata.size(); i++) {
        printf("%s\n", _leveldata[i].c_str());
    }
    printf("\n");
}




void Level::movePlayer(char move, Player &player) {

    int px;
    int py;

    player.getPosition(px, py);

    /*
    printf("X: %d  Y: %d \n", px, py);
        system("PAUSE");
    */

    switch(move) {
    case 'w':
    case 'W':
        processPlayerMove(player, px, py-1);
        break;
    case 's':
    case 'S':
        processPlayerMove(player, px, py+1);
        break;
    case 'a':
    case 'A':
        processPlayerMove(player, px-1, py);
        break;
    case 'd':
    case 'D':
        processPlayerMove(player, px+1, py);
        break;
    case 'x':
    case 'X':
        printStats(player);
        break;
    default:
        printf("Invalid Move!");
        system("PAUSE");
        break;
    }
}




void Level::processPlayerMove(Player &player, int tx, int ty) {
        int px;
        int py;
        player.getPosition(px, py);

        /*
        printf("X: %d  Y: %d \n", px, py);
        printf("tX: %d  tY: %d \n", tx, ty);
        system("PAUSE");
        */

        char moveTile = _leveldata[ty][tx];
        switch(moveTile) {
        case ' ':
            player.setPosition(tx, ty);
            _leveldata[py][px] = ' ';
            _leveldata[ty][tx] = '@';
            break;
        case '#':
            break;
        default:
            battleEnemy(player, tx, ty);
        }
}




void Level::battleEnemy(Player &player, int tx, int ty) {
    int ex;
    int ey;
    int attackRoll;
    int attackResult;
    string enemyName;

    for(int i=0; i<_enemies.size(); i++) {
        _enemies[i].getPosition(ex, ey);

        if(ex == tx && ey == ty) {
            enemyName = _enemies[i].getName();
            //battle
            attackRoll = player.attack();
            attackResult = _enemies[i].takeDamage(attackRoll);
               printf("Player attacked the %s with an attack of %d!\n", enemyName.c_str(), attackRoll);
            system("PAUSE");

            if(attackResult != 0) {
                _leveldata[ty][tx] = ' ';
                print();
                printf("%s Died!\n", enemyName.c_str());
                _enemies[i] = _enemies.back();
                _enemies.pop_back();
                system("PAUSE");
                player.addExperience(attackResult);

                return;
            }

            attackRoll = _enemies[i].attack();
            attackResult = player.takeDamage(attackRoll);
            printf("%s attacked the Player with an attack of %d!\n", enemyName.c_str(), attackRoll);
            system("PAUSE");

            if(attackResult != 0) {
                int px, py;
                player.getPosition(px, py);
                _leveldata[py][px] = 'X';
                print();
                printf("You Died!\n");
                system("PAUSE");

                exit(0);

                return;
            }

            return;
        }
    }
}




void Level::moveEnemies(Player &player) {
    char AImove;
    int px;
    int py;
    int ex;
    int ey;

    player.getPosition(px, py);

    for(int i=0; i<_enemies.size(); i++) {
        AImove = _enemies[i].getMove(px, py);
        _enemies[i].getPosition(ex, ey);

        switch(AImove) {
        case 'w':
            processEnemyMove(player, i, ex, ey-1);
            break;
        case 's':
            processEnemyMove(player, i, ex, ey+1);
            break;
        case 'a':
            processEnemyMove(player, i, ex-1, ey);
            break;
        case 'd':
            processEnemyMove(player, i, ex+1, ey);
            break;
        default:
            break;
        }
    }
}




void Level::processEnemyMove(Player &player, int i, int tx, int ty) {
        int ex;
        int ey;
        _enemies[i].getPosition(ex, ey);

        char moveTile = _leveldata[ty][tx];
        switch(moveTile) {
        case ' ':
            _enemies[i].setPosition(tx, ty);
            _leveldata[ey][ex] = ' ';
            _leveldata[ty][tx] = _enemies[i].getTile();
            break;
        case '#':
            break;
        case '@':
            battlePlayer(player, ex, ey);
            break;
        default:
            break;
        }
}




void Level::battlePlayer(Player &player, int tx, int ty) {
    int ex;
    int ey;
    int attackRoll;
    int attackResult;
    string enemyName;

    for(int i=0; i<_enemies.size(); i++) {
        _enemies[i].getPosition(ex, ey);

        if(ex == tx && ey == ty) {
            enemyName = _enemies[i].getName();

            //battle
            attackRoll = _enemies[i].attack();
            attackResult = player.takeDamage(attackRoll);
            printf("%s attacked the Player with an attack of %d!\n", enemyName.c_str(), attackRoll);
            system("PAUSE");

            if(attackResult != 0) {
                int px, py;
                player.getPosition(px, py);
                _leveldata[py][px] = 'X';
                print();
                printf("You Died!\n");
                system("PAUSE");

                exit(0);

                return;
            }

            attackRoll = player.attack();
            attackResult = _enemies[i].takeDamage(attackRoll);
               printf("Player attacked the %s with an attack of %d!\n", enemyName.c_str(), attackRoll);
            system("PAUSE");

            if(attackResult != 0) {
                _leveldata[ty][tx] = ' ';
                print();
                printf("%s Died!\n", enemyName.c_str());
                _enemies[i] = _enemies.back();
                _enemies.pop_back();
                system("PAUSE");
                player.addExperience(attackResult);

                return;
            }

            return;
        }
    }
}




int Level::getEnemySize() {
    return _enemies.size();
}




void Level::printStats(Player &player) {
    player.printPlayerStats();

    for(int i=0; i<_enemies.size(); i++) {
        _enemies[i].printEnemyStats();
    }

    system("PAUSE");
}
