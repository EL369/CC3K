#include "dwarf.h"
#include <cmath>

Dwarf::Dwarf(): 
    Enemy{100,20,30,0,0,'W',true} { }


void Dwarf::attackPlayer(Vampire & vampire){
    int def = vampire.getDF();
    int atk = attack;
    int damage = ceil((100.0/(100+def))*atk);
    std::cout << "  The damage is: " << damage << std::endl;
    damage *= -1;
    vampire.addHP(damage);
}
