#include "shade.h"
#include <cstdlib>
#include <cmath>
#include <iostream>


Shade::Shade(): 
    Player{125,25,25,0,0,0,0,125,"Shade"} { }

void Shade::accept(Enemy& enemy){
    int i = rand() % 2;
    if (i == 0){
        enemy.attackPlayer(*this);
    }
    else{
        std::cout << enemy.getType() << "Enemy misses attack" << std::endl;
    }
}

void Shade::attackEnemy(std::shared_ptr <Enemy> enemy){
    int def = enemy->getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    damage *= -1;
    enemy->addHP(damage);
}
