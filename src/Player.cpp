#include "Player.h"
#include <random>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <cstdio>




Player::Player()
{
    //constructor sets the initial position
    _x = 1;
    _y = 1;

}

void Player::init(int level, int health, int attack, int defense, int experience) {
    _level = level;
    _health = health;
    _attack = attack;
    _defense = defense;
    _experience = experience;
}


void Player::setPosition(int x, int y)
{
    //sets the position
    _x = x;
    _y = y;

}

void Player::getPosition(int &x, int &y)
{
    //sets the position
    x = _x;
    y = _y;

}

int Player::attack() {
    static default_random_engine randomEngine(time(NULL));
    uniform_int_distribution<int> attackRole(0, _attack);

    return attackRole(randomEngine);
}

void Player::addExperience(int exp) {
    _experience += exp;

    while(_experience > 100) {
        printf("Leveled Up to %d\n", _level);
        printf("You now have %d health, %d, attack, %d defense, %d experience!\n", _health, _attack, _defense, _experience);
        system("PAUSE");
        //level up
        _experience -= 50;
        _level ++;
        _defense += 5;
        _attack += 5;
        _health += 10;
    }
}

int Player::takeDamage(int attack) {
    attack -= _defense;

    if(attack >= 0) {
        _health -= attack;

        if(_health <= 0)
            return 1;
    }

    return 0;
}




void Player::printPlayerStats() {
    printf("\nYou have %d level, %d health, %d attack, %d defense, %d experience!\n",_level, _health, _attack, _defense, _experience);
}
