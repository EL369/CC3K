#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "character.h"
#include "item.h"

class Gold;
class Enemy;

class Player: public Character{
    protected:
    int floorID;
    int chamberID;
    int maxHP;
    shared_ptr<Potion> potion;
    public:
    Player(int, int, int, int, int, int, int, int);
    virtual void accept(shared_ptr <Enemy>);
    virtual void attack(shared_ptr <Enemy>);
    virtual void usePotion();
    virtual void move(std::string);
    int getFloorID();
    int getChamberID();
    int getMaxHP();
    void setFloor(int);
    void setChamber(int);
};

#endif
