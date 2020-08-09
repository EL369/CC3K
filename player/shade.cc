#include "shade.h"
#include <stdlib.h>
#include <iostream>


Shade::Shade(): 
    Player{125,25,25,0,0,0,0, 125} { }

void Shade::accept(Enemy& enemy){
    int i = rand() % 2;
    if (i == 0){
        enemy.attackEnemy(*this);
    }
    else{
        std::cout << "Enemy misses attack" << std::endl;
    }
}
