#ifndef ENEMY_H
#define ENEMY_H

#include "string"

using namespace std;




class Enemy
{
    public:
        Enemy(string name, char tile, int level, int attack, int health, int defense, int experience, int attackRange, int x, int y);

        void setPosition(int x, int y);

        void getPosition(int &x, int &y);

        int attack();

        int takeDamage(int attack);

        string getName();

        char getMove(int px, int py);

        char getTile();

        void printEnemyStats();

    protected:

    private:
        string _name;
        char _tile;

        int _level;
        int _attack;
        int _defense;
        int _health;
        int _experience;
        int _attackRange;

        int _x;
        int _y;
};

#endif // ENEMY_H
