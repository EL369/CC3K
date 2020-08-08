#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "character.h"
#include "treasure.h"
#include "potion.h"


class Gold;
class Enemy;

class Player: public Character{
    protected:
    int floorID;
    int chamberID;
    int maxHP;
    std::shared_ptr<Potion> potion;
    public:
    Player(int, int, int, int, int, int, int, int);
    virtual ~Player();
    virtual void accept(std::shared_ptr <Enemy>) = 0;
    // virtual void attack(std::shared_ptr <Enemy>) = 0;
    // virtual void usePotion();
    void move(std::string);
    int getFloorID();
    int getChamberID();
    int getMaxHP();
    void setFloor(int);
    void setChamber(int);
};

#endif
