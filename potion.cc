#include "potion.h"

Potion::Potion(int row, int col, int effect, std::string type):
    Item{row, col}, effect{effect}, type{type} { }

int Potion::getEffect(){
    return effect;
}
std::string Potion::getType(){
    return type;
}