#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <vector>
#include <memory>

class Player;
class Enemy;
class Potion;
class Treasure;
class Character;

class Chamber{
private:
    std::vector<std::vector<char>> chamber;
    int which;
public:
    void generateRand(char);

    void erase(char);

    void add(char);

    char getPos (int, int);

};

#endif
