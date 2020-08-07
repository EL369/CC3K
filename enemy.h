#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <iostream>
#include <vector>
#include <memory>
#include "character.h"

class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

class Enemy : Character{
private:
    bool isHostile;

public:
    bool getHostile();
    void attack(std::shared_ptr<Shade>);
    void attack(std::shared_ptr<Drow>);
    void attack(std::shared_ptr<Vampire>);
    void attack(std::shared_ptr<Troll>);
    void attack(std::shared_ptr<Goblin>);
    void move();

};

#endif
