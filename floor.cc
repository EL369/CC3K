#include "floor.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "treasure.h"
#include "chamber.h"
#include "character.h"
#include <iostream>
#include <stdlib.h>

Floor::Floor(std::vector<std::vector<char>> grid, int id):grid{grid},id{id}{
}


void Floor::print(){
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 79; ++j) {
            std::cout<<grid[i][j];
        }std::cout<<std::endl;
    }
    std::cout<<"Race: "<<"Gold: "<<std::endl;
    std::cout<<"Hp: "<<std::endl;
    std::cout<<"Atk: "<<std::endl;
    std::cout<<"Def: "<<std::endl;
    std::cout<<"Action:"<<std::endl;
}


std::shared_ptr<Player> Floor::getPlayer(){
    return player;
}

std::vector<std::shared_ptr<Enemy>> Floor::getEnemies(){
    return enemies;
}

std::vector<std::shared_ptr<Potion>> Floor::getPotions(){
    return potions;
}

std::vector<std::shared_ptr<Treasure>> Floor::getTreasures(){
    return treasures;
}

std::vector<std::shared_ptr<Chamber>> Floor::getChambers(){
    return chambers;
}


void Floor::generateChambers(){
    for (int i=0; i<5; ++i) {
        auto chamber = std::make_shared<Chamber> (i, grid);
        chambers.emplace_back(chamber);
    }
}

void Floor::generatePlayer(std::shared_ptr<Player> p){
    int i = rand() % 5;
    std::vector<int> position = (chambers[i])->generateCharRand('@');
    p->setChamber(i);
    p->setRow(position[0]);
    p->setCol(position[1]);
}

void Floor::generatePotion(std::shared_ptr<Potion> p){
    int i = rand() % 5;
    int type = p->getType();
    std::vector<int> position = (chambers[i])->generateCharRand(type);
    // p->setChamber(i);
    p->setRow(position[0]);
    p->setCol(position[1]);
}

void Floor::generateTreasure(std::shared_ptr<Treasure> t){

}

void Floor::generateEnemy(std::shared_ptr<Enemy> e){

}

void Floor::generateStair(){
    int i;
    while(true){
        i = rand() % 5;
        if(i != player->getChamberID()) break;
    }
    (chambers[i])->generateCharRand('\\');
}
