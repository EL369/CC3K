#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <iostream>
#include <vector>
#include <memory>
#include "character.h"
#include "potion.h"
#include "player.h"
#include "player/shade.h"
// #include "enemy/dwarf.h"

class Shade;

class Enemy : public Character{
    protected:
    char type;
    bool isHostile;

    public:
    Enemy(int, int, int, int, int, char, bool);
    char getType();
    bool getHostile();
    virtual void attackPlayer(Shade &);
    // virtual void attackPlayer(Drow &);
    // virtual void attackPlayer(Vampire &);
    // virtual void attackPlayer(Troll &);
    // virtual void attackPlayer(Goblin &);
    // virtual void move() = 0;
};

class Type{
    virtual std::shared_ptr<Enemy> getEnemy() = 0;
    public:
    virtual ~Type() { }
    virtual void setType(const char &) = 0;
};

class concreteType: public Type{
    char type;
    std::shared_ptr<Enemy> getEnemy() override;
    public:
    concreteType(const char&);
    void setType(const char&) override;
};


#endif
