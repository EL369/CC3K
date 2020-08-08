#include "enemy.h"
using namespace std;

shared_ptr<Enemy> concreteLevel::getEnemy() {
    if (level == 'H'){
        return std::shared_ptr<Human> (new Human());
    }
}

concreteLevel::concreteLevel(const char& c):
    level{c} { }

void concreteLevel::setLevel(const char& c){
    level = c;
}

Enemy::Enemy(int hp, int atk, int def, int row, int col, bool hostile):
    Character{hp, atk, def, row, col}, isHostile{hostile} { }

void Enemy::attack(std::shared_ptr<Shade> shade){
    int def = shade->getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    shade->addHP(-damage);
}

bool Enemy::getHostile(){
    return isHostile;
}
