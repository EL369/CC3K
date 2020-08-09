#include "floor.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "treasure.h"
#include "item/shoard.h"
#include "item/normal.h"
#include "item/merchantHoard.h"
#include "item/dHoard.h"
#include "chamber.h"
#include "character.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

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

// std::vector<std::shared_ptr<Enemy>> Floor::getEnemies(){
//     return enemies;
// }

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
    std::cout<<"generate player"<<std::endl;
    std::srand(time(NULL));
    int i = rand() % 5;
    std::cout<<"chamber "<<i<<std::endl;
    std::vector<int> position = (chambers[i])->generateCharRand('@');
    p->setChamber(i);
    p->setRow(position[0]);
    p->setCol(position[1]);
    player = p;
}

void Floor::generatePotion(std::shared_ptr<Potion> p){
    std::srand(time(NULL));
    int i = rand() % 5;
    int type = p->getType();
    char c = '0'+type;
    std::vector<int> position = (chambers[i])->generateCharRand(c);
    // p->setChamber(i);
    p->setRow(position[0]);
    p->setCol(position[1]);
    potions.emplace_back(p);
}

/*
void Floor::generateTreasure(std::shared_ptr<Treasure> t){
     std::srand(time(NULL));
     int i = rand() % 5;
     int type = t->getType(); //getType?
     char c = '0'+type;
     std::vector<int> position = (chambers[i])->generateCharRand(c);
     // t->setChamber(i);
     t->setRow(position[0]);
     t->setCol(position[1]);
     potions.emplace_back(t);
}
*/

// void Floor::generateEnemy(std::shared_ptr<Enemy> e){

// }

void Floor::generateStair(){
    std::cout<<"generate s"<<std::endl;

    int i;
    while(true){
        std::srand(time(NULL));
        i = rand() % 5;
        if(i != player->getChamberID()) break;
    }
    std::cout<<"chamber "<<i<<std::endl;
    (chambers[i])->generateCharRand('\\');
}

void Floor::generateAll(){
    generateChambers();
    std::shared_ptr<Player> p = std::make_shared<Shade>();
    generatePlayer(p);
    generateStair();
    // generate 10 rand potions
    for(int i=0; i<10; ++i){
        std::srand(time(NULL));
        int type = rand() % 6;
        std::shared_ptr<Potion> potion = std::make_shared<Potion>(0, 0, 0, type);
        generatePotion(potion);
        potions.emplace_back(potion);
    }
    // gold: 5/8 chance of normal, 1/8 dragon hoard, 2/8 small hoard
    /*
    for(int i=0; i<10; ++i){
         std::srand(time(NULL));
         int type = rand() % 8;
         std::shared_ptr<Treasure> t;
         if(type < 5){
             std::shared_ptr<Treasure> t = std::make_shared<Normal>();
         }else if (type == 7){
             std::shared_ptr<Treasure> t = std::make_shared<Dhoard>();
         }else{
             std::shared_ptr<Treasure> t = std::make_shared<Shoard>();
         }
         generateTreasure(t);
         treasures.emplace_back(t);
    }
    */
    print();
}

void Floor::move(std::shared_ptr<Character>, int initX, int initY, int newX, int newY){
    if (grid[newY][newX] == '.' ){
        char c = grid[initY][initX];
        grid[newY][newX] = c;
        grid[initY][initX] = '.';
    }
}


// Enemies detect whether there's player within 1 block around. 
void Floor::enemyAttackMove(){
    int prow = player->getRow();
    int pcol = player->getCol();
    for (int y = prow-1; y <= prow+1; y++){
        for (int x = pcol-1; x <= pcol+1; x++){
            if (grid[y][x] == 'H'){
                int enemyAt = 0;
                int sizeEnemy = enemies.size();
                for(int i = 0; i < sizeEnemy; i++){
                    if(enemies[i]->getCol() == x && enemies[i]->getRow() == y){
                        enemyAt = i;
                        break;
                    }
                }
                if (enemies[enemyAt]->getHostile() == true){
                    player->accept(*enemies[enemyAt]);
                }
            }
            /*
            else if (grid[y][x] == 'D'){

            }
            */
        }
    }
}
