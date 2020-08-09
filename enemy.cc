#include "enemy.h"
#include <cmath>
#include "enemy/human.h"

using namespace std;

shared_ptr<Enemy> concreteLevel::getEnemy() {
    if (level == 'H'){
        return shared_ptr<Human> (new Human);
    }
    /*
    else if (level == 'W'){
        return shared_ptr<Dwarf> (new Dwarf);
    }
    else if (level == 'V'){
        return shared_ptr<Vampire> (new Vampire);
    }

    */
}

concreteLevel::concreteLevel(const char& c):
    level{c} { }

void concreteLevel::setLevel(const char& c){
    level = c;
}

Enemy::Enemy(int hp, int atk, int def, int row, int col, bool hostile):
    Character{hp, atk, def, row, col}, isHostile{hostile} { }

void Enemy::attackEnemy(Shade& shade){
    int def = shade.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    shade.addHP(-damage);
}

/*
void Enemy::attackEnemy(Drow& drow){
    int def = drow.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    drow.addHP(-damage);
}

void Enemy::attackEnemy(Vampire& vampire){
    int def = vampire.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    vampire.addHP(-damage);
}

void Enemy::attackEnemy(Troll& troll){
    int def = troll.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    troll.addHP(-damage);
}

void Enemy::attackEnemy(Goblin& goblin){
    int def = goblin.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    goblin.addHP(-damage);
}
*/

bool Enemy::getHostile(){
    return isHostile;
}
