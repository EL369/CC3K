#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <iostream>
#include <vector>
#include <memory>
#include "character.h"
#include "potion.h"

class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

class Enemy : public Character{
protected:
    bool isHostile;

public:
    bool getHostile();
    virtual void attack(std::shared_ptr<Shade>);
    virtual void attack(std::shared_ptr<Drow>);
    virtual void attack(std::shared_ptr<Vampire>);
    virtual void attack(std::shared_ptr<Troll>);
    virtual void attack(std::shared_ptr<Goblin>);
    virtual void move();

};

#endif
