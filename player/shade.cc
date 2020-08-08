#include "shade.h"

Shade::Shade(): 
    Player{125,25,25,0,0,0,0, 125} { }

void accept(std::shared_ptr <Enemy> enemy){
    enemy->attack(*this);
}
