#include "treasure.h"

Treasure::Treasure(int row, int col, int amt, int type):
    Item{row, col}, amount{amt}, pick{false}, type{type} {}

int Treasure::getAmt(){
    return amount;
}

bool Treasure::getPick(){
    return pick;
}

void Treasure::setAmt(int amt){
    this->amount = amt;
}

void Treasure::setPick(bool pick){
    this->pick = pick;
}

int Treasure::getType(){
    return type;
}
