#include "player.h"
#include "enemy.h"


Player::Player(int h, int atk, int def, int row, int col, int floor, int chamber, int maxHP):
    Character{h, atk, def, row, col}, floorID{floor}, chamberID{chamber}, maxHP{maxHP}, gold{0}, alive{true} { }

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
            alive = false;
        }
        else{
            health -= 10;
        }
    }
    else if (type == 4){
        if (attack-5 <= 0){
            attack = 0;
            alive = false;
        }
        else{
            attack -= 5;
        }
    }
    else if (type == 5){
        if (defense-5 <= 0){
            defense = 0;
            alive = false;
        }
        else{
            defense -= 5;
        }
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

int Player::getGold(){
    return gold;
}

void Player::setFloor(int id){
    floorID = id;
}

void Player::setChamber(int id){
    chamberID = id;
}

void Player::addGold(int g){
    gold += g;
}

void Player::setAlive(bool b){
    alive = b;
}

void Player::addPotion(std::shared_ptr<Potion> potion){
    tempPotion.emplace_back(potion);
}

void Player::removeTempPotion(){
    int size = tempPotion.size();
    for(int i = 0; i < size; i++){
        if (tempPotion[i]->getType() == 1){
            if (attack-5 <= 0){
                attack = 0;
                alive = false;
                break;
            }
            else{ attack -= 5; }
        }
        else if (tempPotion[i]->getType() == 2){
            if (defense-5 <= 0){
                defense = 0;
                alive = false;
                break;
            }
            else{ defense -= 5; }
        }
        else if (tempPotion[i]->getType() == 4){
            attack += 5;
        }
        else if (tempPotion[i]->getType() == 5){
            defense += 5;
        }
    }
}
