#ifndef PLAYER_H
#define PLAYER_H

using namespace std;




//A class to store the info about the player
class Player
{
    public:
        Player();

        void init(int level, int health, int attack, int defense, int experience);

        void setPosition(int x, int y);

        void getPosition(int &x, int &y);

        int attack();

        void addExperience(int exp);

        int takeDamage(int attack);

        void printPlayerStats();

    protected:

    private:
        //position
        int _x;
        int _y;

        //properties
        int _level, _health, _attack, _defense, _experience;
};

#endif // PLAYER_H
