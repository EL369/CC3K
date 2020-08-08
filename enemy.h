#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <iostream>
#include <vector>
#include <memory>
#include "character.h"
#include "potion.h"
#include "player.h"
#include "player/shade.h"
#include "enemy/human.h"



class Enemy;

class Level{
    virtual std::shared_ptr<Enemy> getEnemy() = 0;
    public:
    virtual ~Level() { }
    virtual void setLevel(const char &) = 0;
};

class concreteLevel: public Level{
    char level;
    std::shared_ptr<Enemy> getEnemy() override;
    public:
    concreteLevel(const char&);
    void setLevel(const char&) override;
};

class Enemy : public Character{
    protected:
    bool isHostile;

    public:
    Enemy(int, int, int, int, int, bool);
    bool getHostile();
    virtual void attack(std::shared_ptr<Shade>);
    //virtual void attack(std::shared_ptr<Drow>);
    //virtual void attack(std::shared_ptr<Vampire>);
    // virtual void attack(std::shared_ptr<Troll>);
    // virtual void attack(std::shared_ptr<Goblin>);
    // virtual void move() = 0;
};

#endif
