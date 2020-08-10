#include "floor.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "treasure.h"
#include "treasure/sHoard.h"
#include "treasure/gold.h"
#include "treasure/mHoard.h"
#include "treasure/dHoard.h"
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
    std::cout<<"generate potion: "<<c<<std::endl;
    std::vector<int> position = (chambers[i])->generateCharRand(c);
    // p->setChamber(i);
    p->setRow(position[0]);
    p->setCol(position[1]);
    potions.emplace_back(p);
}


void Floor::generateTreasure(std::shared_ptr<Treasure> t){
     std::srand(time(NULL));
     int i = rand() % 5;
     int type = t->getType(); //getType?
     char c = '0'+type;
    std::cout<<"generate treasure: " << c<<std::endl;
     std::vector<int> position = (chambers[i])->generateCharRand(c);
     // t->setChamber(i);
     t->setRow(position[0]);
     t->setCol(position[1]);
     treasures.emplace_back(t);
}


// void Floor::generateEnemy(std::shared_ptr<Enemy> e){
//     std::cout<<"generate enemy"<<std::endl;
//     std::srand(time(NULL));
//     int i = rand() % 5;
//     std::cout<<"chamber "<<i<<std::endl;
//     if()
//     std::vector<int> position = (chambers[i])->generateCharRand('@');
//     // e->setChamber(i);
//     e->setRow(position[0]);
//     e->setCol(position[1]);
//     enemies.emplace_back(e);
// }

void Floor::generateStair(){
    std::cout<<"generate stair"<<std::endl;

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
    //6 - normal gold pile, 7 - small hoard, 8 - merchant hoard (DNE), 9 - dragon hoard
    for(int i=0; i<10; ++i){
        std::srand(time(NULL));
        int type = rand() % 8;
        std::shared_ptr<Treasure> t;
        if(type < 5){
            t = std::make_shared<Gold>();
        }else if (type == 7){
            t = std::make_shared<Dhoard>();
        }else{
            t = std::make_shared<Shoard>();
        }
        generateTreasure(t);
        treasures.emplace_back(t);
    }
    
    print();
}

void Floor::move(std::shared_ptr<Character>, int initX, int initY, int newX, int newY){
    if (grid[newY][newX] == '.' ){
        char c = grid[initY][initX];
        grid[newY][newX] = c;
        grid[initY][initX] = '.';
    }
}

int Floor::treasureAt(int row, int col){
    int sizeTreasure = treasures.size();
    int at = -1;
    for(int i = 0; i < sizeTreasure; i++){
        if(treasures[i]->getCol() == col && treasures[i]->getRow() == row){
            at = i;
            break;
        }
    }
    return at;
}

int Floor::potionAt(int row, int col){
    int sizePotion = potions.size();
    int at = -1;
    for(int i = 0; i < sizePotion; i++){
        if(potions[i]->getCol() == col && potions[i]->getRow() == row){
            at = i;
            break;
        }
    }
    return at;
}

//helper
bool Floor::isRegularEnemy(int row, int col){
    if (grid[row][col] == 'W' || grid[row][col] == 'E' || grid[row][col] == 'O' || grid[row][col] == 'L'){
            return true;
        }
    else{
        return false;
    }
}

// return the index of enemy at grid[row][col] in the vector of enemies. 
int Floor::enemyAt(int row, int col){
    int sizeEnemy = enemies.size();
    int at = -1;
    for(int i = 0; i < sizeEnemy; i++){
        if(enemies[i]->getCol() == col && enemies[i]->getRow() == row){
            at = i;
            break;
        }
    }
    return at;
}

// Enemies detect whether there's player within 1 block around. 
void Floor::enemyAttackMove(){
    int prow = player->getRow();
    int pcol = player->getCol();
    for (int y = prow-1; y <= prow+1; y++){
        for (int x = pcol-1; x <= pcol+1; x++){
            if (isRegularEnemy(y, x) || grid[y][x] == 'H' || grid[y][x] == 'M'){
                int at = enemyAt(y, x);
                if (enemies[at]->getHostile() == true){
                    player->accept(*enemies[at]);
                }
            }
            /*
            else if (grid[y][x] == 'D'){

            }
            */
        }
    }
    if (player->getHP() <= 0){
        player->setAlive(false);
    }
}

std::vector<int> Floor::nextMove(std::string str){
    std::vector<int> pos;
    int row = player->getRow();
    int col = player->getCol();
    if (str == "no"){
        row -= 1;
    }
    else if (str == "so"){
        row += 1;
    }
    else if (str == "ea"){
        col += 1;
    }
    else if (str == "we"){
        col -= 1;
    }
    else if (str == "ne"){
        row -= 1;
        col += 1;
    }
    else if (str == "nw"){
        row -= 1;
        col -= 1;
    }
    else if (str == "se"){
        row += 1;
        col += 1;
    }
    else if (str == "sw"){
        row += 1;
        col -= 1;
    }
    pos.emplace_back(row);
    pos.emplace_back(col);
    return pos;
}

void Floor::playerAttack(std::string str){
    std::vector<int> pos = nextMove(str);
    int y = pos[0];
    int x = pos[1];
    if (isRegularEnemy(y, x) || grid[y][x] == 'H' || grid[y][x] == 'M' || grid[y][x] == 'D'){
        int at = enemyAt(y, x);
        player->attackEnemy(enemies[at]);
        // if the enemy that player attack is a merchant, all merchants are set to be hostile.  
        if (grid[y][x] == 'H'){
            int s = enemies.size();
            for(int i = 0; i < s; i++){
                if (enemies[i]->getType() == 'M'){
                    enemies[i]->setHostile(true);
                }
            }
        }
        if(enemies[at]->getHP() <= 0){
            std::cout << enemies[at]->getType() << " is killed" << std::endl;
            int size = enemies.size();
            size -= 1;
            for (int j = at; j < size; j++){
                enemies[j] = enemies[j+1];
            }
            enemies.resize(size);
            if (isRegularEnemy(y,x)){
                int i = rand() % 2;
                if (i == 0){
                    player->addGold(1);
                    std::cout << "A small pile is added to your pocket" << std::endl;
                }
                else{
                    player->addGold(2);
                    std::cout << "A Normal pile is added to your pocket" << std::endl;
                }
                grid[y][x] = '.';
            }
            else if (grid[y][x] == 'H'){
                grid[y][x] = '6';
                auto normal1 = std::make_shared<Gold>();
                treasures.emplace_back(normal1);
                int acc = 1;
                // Another normal pile a generated nearby. 
                for(int i = y-1 ; i <= y+1; i++){
                    if (acc == 1){
                        break;
                    }
                    for(int j = x-1 ; j <= x+1; j++){
                        if (grid[i][j] == '.'){
                            grid[i][j] = '6';
                            auto normal = std::make_shared<Gold>();
                            treasures.emplace_back(normal);
                            acc += 1;
                            break;
                        }
                    }
                }
                std::cout << "Two Normal pile is dropped" << std::endl;
            }
            /*
            else if (grid[y][x] == 'M'){
                auto merchantH = std::make_shared<Mhoard>();
                treasures.emplace_back(merchantH);
                grid[y][x] = '8';
            }
            else{
                grid[y][x] = '.';
            }
            */
        }
    }
}


void Floor::playerMove(std::string str){
    std::vector<int> pos = nextMove(str);
    int y = pos[0];
    int x = pos[1];
    if (grid[y][x] == '.' || grid[y][x] == '+' ||  grid[y][x] == '#'){
        player->move(str);
    }
    else if (grid[y][x] == '6' || grid[y][x] == '7' || grid[y][x] == '8' || grid[y][x] == '9'){
        int at = treasureAt(y, x);
        if (treasures[at]->getPick() == true){
            int amt = treasures[at]->getAmt();
            player->addGold(amt);
            int size = treasures.size();
            size -= 1;
            for (int j = at; j < size; j++){
                treasures[j] = treasures[j+1];
            }
            treasures.resize(size);
            player->move(str);
        }
        else{
            std::cout << "treasures cannot be picked" << std::endl;
        }
    }
    else{
        std::cout << "invalid movement" << std::endl;
    }
}

void Floor::playerUsePotion(std::string str){
    std::vector<int> pos = nextMove(str);
    int y = pos[0];
    int x = pos[1];
    if (grid[y][x] == '0' || grid[y][x] == '1' || grid[y][x] == '2' || grid[y][x] == '3'
            || grid[y][x] == '4' || grid[y][x] == '5'){
        int at = potionAt(y, x);
        if (grid[y][x] == '0' || grid[y][x] == '3'){
            player->usePotion(potions[at]);
        }
        else{
            player->usePotion(potions[at]);
            player->addPotion(potions[at]);
        }
        int size = potions.size();
        size -= 1;
        for (int j = at; j < size; j++){
            potions[j] = potions[j+1];
        }
        potions.resize(size);
        grid[y][x] = '.';
        player->move(str);
    }
    else{
        std::cout << "No potion in this direction" << std::endl;
    }
}

// if returned {0, 0} means char not found
// std::vector<int> Floor::existNear(char a, int row, int col){
//     std::vector<int> pos;
//     int r;
//     int c;
//     for (int y = row-1; y <= row+1; y++){
//         for (int x = col-1; x <= col+1; x++){
//             if(grid[row][col] == a){
//                 r = y;
//                 c = x;
//             }
//         }
//     }
//     pos.emplace_back(r);
//     pos.emplace_back(c);
//     return pos;
// }

// void Floor::enemyAttackMove(std::shared_ptr<Enemy> e){
//     int eRow = e->getRow();
//     int eCol = e->getCol();
//     int pRow = player->getRow();
//     int pCol = player->getCol();
//     if (pRow >= eRow-1 && pRow <= eRow && pCol >= eCol-1 && pCol <= eCol+1){
//         player->accept(*e);  // Attack method need to specify player type.
//     }
// }

