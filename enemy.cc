#include "enemy.h"
#include <cmath>
#include "enemy/human.h"

using namespace std;

shared_ptr<Enemy> concreteType::getEnemy() {
    shared_ptr<Enemy> e;
    if (type == 'H'){
        e = make_shared<Human>();
    }
    /*
    else if (type == 'W'){
        return shared_ptr<Dwarf> (new Dwarf);
    }
    else if (type == 'V'){
        return shared_ptr<Vampire> (new Vampire);
    }

    */
   return e;
}

concreteType::concreteType(const char& c):
    type{c} { }

void concreteType::setType(const char& c){
    type = c;
}

Enemy::Enemy(int hp, int atk, int def, int row, int col, char type, bool hostile):
    Character{hp, atk, def, row, col}, type{type}, isHostile{hostile} { }

char Enemy::getType(){
    return type;
}


bool Enemy::getHostile(){
    return isHostile;
}

void Enemy::attackPlayer(Shade& shade){
    int def = shade.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    shade.addHP(-damage);
}

/*
void Enemy::attackPlayer(Drow& drow){
    int def = drow.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    drow.addHP(-damage);
}

void Enemy::attackPlayer(Vampire& vampire){
    int def = vampire.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    vampire.addHP(-damage);
}

void Enemy::attackPlayer(Troll& troll){
    int def = troll.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    troll.addHP(-damage);
}

void Enemy::attackPlayer(Goblin& goblin){
    int def = goblin.getDF();
    int atk = attack;
    double dmg = (100/(100+def)*atk);
    int damage = ceil(dmg);
    goblin.addHP(-damage);
}
*/
