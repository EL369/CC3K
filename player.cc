#include "player.h"
#include "enemy.h"


Player::Player(int h, int atk, int def, int row, int col, int floor, int chamber, int maxHP):
    Character{h, atk, def, row, col}, floorID{floor}, chamberID{chamber}, maxHP{maxHP} { }

Player::~Player(){}

void Player::usePotion(std::shared_ptr<Potion> potion){
    int type = potion->getType();
    if (type == 0){
        if (health+10 >= maxHP){
            health = maxHP;
        }
        else{
            health += 10;
        }
    }
    else if (type == 1){
        attack += 5;
    }
    else if (type == 2){
        defense += 5;
    }
    else if (type == 3){
        if (health-10 <= 0){
            health = 0;
        }
        else{
            health -= 10;
        }
    }
    else if (type == 4){
        attack -= 5;
    }
    else if (type == 5){
        defense -= 5;
    }
}

void Player::move(std::string str){
    if (str == "no"){
        moveRow(-1);
    }
    else if (str == "so"){
        moveRow(1);
    }
    else if (str == "ea"){
        moveCol(1);
    }
    else if (str == "we"){
        moveCol(-1);
    }
    else if (str == "ne"){
        moveRow(-1);
        moveCol(1);
    }
    else if (str == "nw"){
        moveRow(-1);
        moveCol(-1);
    }
    else if (str == "se"){
        moveRow(1);
        moveCol(1);
    }
    else if (str == "sw"){
        moveRow(1);
        moveCol(-1);
    }
    // else: throw exception?
}

int Player::getFloorID(){
    return floorID;
}

int Player::getChamberID(){
    return chamberID;
}
    
int Player::getMaxHP(){
    return maxHP;
}

void Player::setFloor(int id){
    floorID = id;
}

void Player::setChamber(int id){
    chamberID = id;
}

