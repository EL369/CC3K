#include "potion.h"

Potion::Potion(int row, int col, int effect, int type):
    Item{row, col}, effect{effect}, type{type} { }

int Potion::getEffect(){
    return effect;
}
int Potion::getType(){
    return type;
}
