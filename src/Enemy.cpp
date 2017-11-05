#include "Enemy.h"
#include <random>
#include <ctime>
#include <cstdio>
#include <conio.h>




Enemy::Enemy(string name, char tile, int level, int attack, int health, int defense, int experience, int attackRange, int x, int y)
{
    _name = name;
    _tile = tile;
    _level = level;
    _attack = attack;
    _health = health;
    _defense = defense;
    _experience = experience;
    _attackRange = attackRange;
    _x = x;
    _y = y;
}


void Enemy::setPosition(int x, int y)
{
    //sets the position
    _x = x;
    _y = y;

}

void Enemy::getPosition(int &x, int &y)
{
    //sets the position
    x = _x;
    y = _y;

}

int Enemy::attack() {
    static default_random_engine randomEngine(time(NULL));
    uniform_int_distribution<int> attackRole(0, _attack);

    return attackRole(randomEngine);
}

int Enemy::takeDamage(int attack) {
    attack -= _defense;

    if(attack >= 0) {
        _health -= attack;

        if(_health <= 0)
            return _experience;
    }

    return 0;
}

string Enemy::getName() {
    return _name;
}

char Enemy::getMove(int px, int py) {
    static default_random_engine randomEngine(time(NULL));
    uniform_int_distribution<int> moveRoll(0, 7);

    int distance;
    int dx;
    int dy;
    int adx;
    int ady;

    dx = _x - px;
    dy = _y - py;
    adx = abs(dx);
    ady = abs(dy);
    distance = adx + ady;

    if(distance < _attackRange) {
        printf("%s saw you!\n", _name.c_str());
        printf("%s has %d health, %d attack, %d defense, %d experience!\n", _name.c_str(), _health, _attack, _defense, _experience);
        system("PAUSE");
        if(adx > ady) {
            if(dx > 0)
                return 'a';
            else
                return 'd';
        }
        else {
            if(dy > 0)
                return 'w';
            else
                return 's';
        }
    }

    int randomMove = moveRoll(randomEngine);
    switch(randomMove) {
    case 0:
        return 'w';
    case 1:
        return 's';
    case 2:
        return 'a';
    case 3:
        return 'd';
    default:
        return '.';
    }
}

char Enemy::getTile() {
    return _tile;
}




void Enemy::printEnemyStats() {
    printf("%s has %d level, %d health, %d attack, %d defense, %d experience!\n", _name.c_str(), _level, _health, _attack, _defense, _experience);
}
