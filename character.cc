#include "character.h"
#include "treasure/shoard.h"
#include "treasure/gold.h"
#include "treasure/mHoard.h"
#include "treasure/dHoard.h"

Character::Character(int h, int atk, int def, int row, int col):
    health{h}, attack{atk}, defense{def}, row{row}, col{col} { }

int Character::getHP(){
    return health;
}

int Character::getAtk(){
    return attack;
}

int Character::getDF(){
    return defense;
}


int Character::getRow(){
    return row;
}

int Character::getCol(){
    return col;
}

void Character::moveRow(int r){
    row += r;
}

void Character::moveCol(int c){
    col += c;
}

void Character::addHP(int h){
    health += h;
}

void Character::addAtk(int atk){
    attack += atk;
}

void Character::addDF(int def){
    defense += def;
}

void Character::setRow(int r){
    row = r;
}

void Character::setCol(int c){
    col = c;
}
