#include "floor.h"
#include "player.h"
#include "enemy.h"
#include "enemy/human.h"
#include "enemy/dwarf.h"
#include "enemy/elf.h"
#include "enemy/halfling.h"
#include "enemy/dragon.h"
#include "enemy/merchant.h"
#include "enemy/orcs.h"

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
#include <iomanip>
#include <algorithm>
#include <vector>


Floor::Floor(std::vector<std::vector<char>> grid, int id):grid{grid},id{id}{
}


void Floor::print(){
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 79; ++j) {
            std::cout<<grid[i][j];
        }std::cout<<std::endl;
    }
    std::cout<<"Race: "<< player->getType() <<" Gold: " << player->getGold();
    std::cout<<std::setw(56)<<std::right<< "Floor "<< id+1 <<std::endl;
    std::cout<<"Hp: "<< player->getHP()<<std::endl;
    std::cout<<"Atk: "<< player->getAtk() <<std::endl;
    std::cout<<"Def: "<< player->getDF() <<std::endl;
    std::cout<<"Action: "<< action <<std::endl;
    action = "";
}

int Floor::getId(){
    return id;
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

void Floor::setAction(std::string s){
    action += s;
}

bool Floor::getReachStair(){
    return reachStair;
}

void Floor::generateChambers(){
    for (int i=0; i<5; ++i) {
        auto chamber = std::make_shared<Chamber> (i, grid);
        chambers.emplace_back(chamber);
    }
}

void Floor::generatePlayer(std::shared_ptr<Player> p){
    // std::cout<<"generate player"<<std::endl;
    std::srand(time(NULL));
    int i = rand() % 5;
    // std::cout<<"chamber "<<i<<std::endl;
    std::vector<int> position = (chambers[i])->generateCharRand('@');
    p->setChamber(i);
    p->setRow(position[1]);
    p->setCol(position[0]);
    player = p;
}

void Floor::generatePotion(std::shared_ptr<Potion> p){
    std::srand(time(NULL));
    int i = rand() % 5;
    // std::cout<<"generate potion: "<<c<<std::endl;
    std::vector<int> position = (chambers[i])->generateCharRand('P');
    // p->setChamber(i);
    p->setRow(position[1]);
    p->setCol(position[0]);
    potions.emplace_back(p);
}


void Floor::generateTreasure(std::shared_ptr<Treasure> t){
     std::srand(time(NULL));
     int i = rand() % 5;
    // std::cout<<"generate treasure: " << c<<std::endl;
     std::vector<int> position = (chambers[i])->generateCharRand('G');
     // t->setChamber(i);
     t->setRow(position[1]);
     t->setCol(position[0]);
     treasures.emplace_back(t);
}


void Floor::generateEnemy(std::shared_ptr<Enemy> e){
    std::srand(time(NULL));
    int i = rand() % 5;
    std::vector<int> position = (chambers[i])->generateCharRand(e->getType());
    // e->setChamber(i);
    e->setRow(position[1]);
    e->setCol(position[0]);
    enemies.emplace_back(e);
}


void Floor::generateStair(){
    int i;
    while(true){
        std::srand(time(NULL));
        i = rand() % 5;
        if(i != player->getChamberID()) break;
    }
    (chambers[i])->generateCharRand('\\');
}

void Floor::generateAll(std::shared_ptr<Player> p){
    generateChambers();
    generatePlayer(p);
    generateStair();
    // generate 10 rand potions
    for(int i=0; i<10; ++i){
        std::srand(time(NULL));
        int type = rand() % 6;
        std::shared_ptr<Potion> potion = std::make_shared<Potion>(0, 0, 0, type);
        generatePotion(potion);
    }
    // gold: 5/8 chance of normal, 1/8 dragon hoard, 2/8 small hoard
    //6 - normal gold pile, 7 - small hoard, 8 - merchant hoard (DNE), 9 - dragon hoard
    for(int i=0; i<10; ++i){
        std::srand(time(NULL));
        int type = rand() % 8;
        std::shared_ptr<Treasure> t;
        std::shared_ptr<Dragon> d;
        if(type < 5){
            t = std::make_shared<Gold>();
        }
        else if (type <= 5){
            std::shared_ptr<Dhoard> hoard;
            hoard = std::make_shared<Dhoard>();
            d = std::make_shared<Dragon>();
            d->setDhoard(hoard);
            enemies.emplace_back(d);
            generateTreasure(hoard);
            int pos = treasures.size();
            int y = treasures[pos-1]->getRow();
            int x = treasures[pos-1]->getCol();
            int acc = 0;
            for (int i = y-1; i <= y+1; i++){
                if (acc == 1){
                    break;
                }
                for (int j = x-1; j <= x+1; j++){
                    if (grid[i][j] == '.'){
                        d->setRow(i);
                        d->setCol(j);
                        grid[i][j] = 'D';
                        acc++;
                        break;
                    }
                }
            }
            // treasures.emplace_back(hoard);
            continue;
        }
        else{
            t = std::make_shared<Shoard>();
        }
        generateTreasure(t);
        // treasures.emplace_back(t);
    }
    for(int i=0; i<20; ++i){
        concreteType t{'H'};
        std::shared_ptr<Enemy> e;
        std::srand(time(NULL));
        int type = rand() % 18;
        if(type < 4){
            t.setType('H');
            e = t.getEnemy();
        }
        else if (type < 7){
            t.setType('W');
            e = t.getEnemy();
        }
        else if (type < 12){
            t.setType('L');
            e = t.getEnemy();
        }
        else if (type < 14){
            t.setType('E');
            e = t.getEnemy();
        }
        else if (type < 16){
            t.setType('O');
            e = t.getEnemy();
        }
        else{
            t.setType('M');
            e = t.getEnemy();
        }
        generateEnemy(e);
        // enemies.emplace_back(e);
    }
    print();
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
void Floor::enemyAttackPlayer(){
    int prow = player->getRow();
    int pcol = player->getCol();
    int acc = -1;
    for (int y = prow-1; y <= prow+1; y++){
        for (int x = pcol-1; x <= pcol+1; x++){
            if (isRegularEnemy(y, x) || grid[y][x] == 'H' || grid[y][x] == 'M' || grid[y][x] == 'D'){
                int at = enemyAt(y, x);
                if (at == acc){
                    break;
                }
                if (enemies[at]->getHostile() == true){
                    player->accept(*enemies[at]);
                    action += "Enemy attacked player. ";
                    acc = at;
                }
            }
            else if (grid[y][x] == 'G'){
                int at = treasureAt(y, x);
                if (treasures[at]->getType() == 9){
                    int size = enemies.size();
                    for(int i = 0; i < size; i++){
                        if (i == acc){
                            break;
                        }
                        std::shared_ptr<Dragon> dragon;
                        if (enemies[i]->getType() == 'D'){
                            dragon = std::dynamic_pointer_cast<Dragon> (enemies[i]);
                        }
                        else{
                            continue;
                        }
                        if (dragon->getDhoard() == treasures[at]){
                            player->accept(*enemies[i]);
                            acc = i;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (player->getHP() <= 0){
        player->setAlive(false);
        action += "Your character is dead. GG";
    }
}

void Floor::EnemymoveHelper(int at){
    std::vector<int> pos;
    int acc = 0;
    int erow = enemies[at]->getRow();
    int ecol = enemies[at]->getCol();
    for(int i = erow-1; i <= erow+1; i++){
        for(int j = ecol-1; j <= ecol+1; j++){
            if (grid[i][j] == '.'){
                acc += 1;
                pos.emplace_back(i);
                pos.emplace_back(j);
            }
        }
    }
    int k = rand() % acc;
    k *= 2;
    int y = pos[k];
    int x = pos[k+1];
    enemies[at]->setRow(y);
    enemies[at]->setCol(x);
    grid[y][x] = enemies[at]->getType();
    grid[erow][ecol] = '.';
}

void Floor::Enemymove(){
    std::vector<int> track;
    for(int y = 0; y < 25; y++){
        for (int x = 0; x < 79; x++){
            if (isRegularEnemy(y,x) || grid[y][x] == 'H' || grid[y][x] == 'M'){
                int prow = player->getRow();
                int pcol = player->getCol();
                if (y >= prow-1 && y <= prow + 1 && x >= pcol-1 && x <= pcol + 1){
                    break;
                }
                int at = enemyAt(y, x);
                std::vector<int>::iterator it = std::find(track.begin(), track.end(), at);
                if (it == track.end()){
                    track.emplace_back(at);
                    EnemymoveHelper(at);
                }
            }
        }
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
        action += "Player attacked an enemy. ";
        // if the enemy that player attack is a merchant, all merchants are set to be hostile.  
        if (grid[y][x] == 'M'){
            int s = enemies.size();
            for(int i = 0; i < s; i++){
                if (enemies[i]->getType() == 'M'){
                    enemies[i]->setHostile(true);
                }
            }
        }
        if(enemies[at]->getHP() <= 0){
            std::string s;
            char c = enemies[at]->getType();
            s.push_back(c);
            action += "  " + s + " is killed!! ";
            if (isRegularEnemy(y,x)){
                std::srand(time(NULL));
                int i = rand() % 2;
                if (i == 0){
                    player->addGold(1);
                    action += "A small pile of gold is added to your pocket";
                }
                else{
                    player->addGold(2);
                    action += "A normal pile of gold is added to your pocket" ;
                }
                grid[y][x] = '.';
            }
            else if (grid[y][x] == 'H'){
                grid[y][x] = 'G';
                auto normal1 = std::make_shared<Gold>();
                normal1->setRow(y);
                normal1->setCol(x);
                treasures.emplace_back(normal1);
                int acc = 0;
                // Another normal pile a generated nearby. 
                for(int i = y-1 ; i <= y+1; i++){
                    if (acc == 1){
                        break;
                    }
                    for(int j = x-1 ; j <= x+1; j++){
                        if (grid[i][j] == '.'){
                            grid[i][j] = 'G';
                            auto normal = std::make_shared<Gold>();
                            normal->setRow(i);
                            normal->setCol(j);
                            treasures.emplace_back(normal);
                            acc += 1;
                            break;
                        }
                    }
                }
                std::cout<< "  Two normal piles of gold is dropped" << std::endl;
            }
            else if (grid[y][x] == 'M'){
                auto merchantH = std::make_shared<Mhoard>();
                grid[y][x] = 'G';
                merchantH->setRow(y);
                merchantH->setCol(x);
                treasures.emplace_back(merchantH);
                std::cout << "  Merchant Hoard is dropped!" << std::endl;
            }
            else{
                std::shared_ptr<Dragon> dragon = std::dynamic_pointer_cast<Dragon> (enemies[at]);
                grid[y][x] = '.';
                dragon->getDhoard()->setPick(true);
                std::cout << "  Dragon Hoard can be picked now!";
            }
            enemies.erase(enemies.begin()+at);
        }
    }
}

void Floor::clearFloor(){
    for (int i = 0; i < enemies.size(); i++){
        int x = enemies[0]->getCol();
        int y = enemies[0]->getRow();
        grid[y][x] = '.';
        enemies.erase(enemies.begin());
    }
    enemies.clear();
    for (int i = 0; i < treasures.size(); i++){
        int x = treasures[0]->getCol();
        int y = treasures[0]->getRow();
        grid[y][x] = '.';
        treasures.erase(treasures.begin());
    }
    treasures.clear();
    for (int i = 0; i < potions.size(); i++){
        int x = potions[0]->getCol();
        int y = potions[0]->getRow();
        grid[y][x] = '.';
        potions.erase(potions.begin());
    }
    potions.clear();
    for (int i = 0; i < chambers.size(); i++){
        chambers.erase(chambers.begin());
    }
    chambers.clear();
    int x = player->getCol();
    int y = player->getRow();
    grid[y][x] = '.';
}


void Floor::playerMove(std::string str){
    std::vector<int> pos = nextMove(str);
    int y = pos[0];
    int x = pos[1];
    int r = player->getRow();
    int c = player->getCol();
    if (grid[y][x] == '.' || grid[y][x] == '+' ||  grid[y][x] == '#'){
        player->move(str);
        grid[r][c] = player->getOrigin();
        player->setOrigin(grid[y][x]);
        grid[y][x] = '@';
        action += "Player moved in "+str+" direction. ";
    }
    else if(grid[y][x] == '\\'){
        reachStair = true;
        grid[y][x] = '@';
    }
    else if (grid[y][x] == 'G'){
        int at = treasureAt(y, x);
        if (treasures[at]->getPick() == true){
            int amt = treasures[at]->getAmt();
            player->addGold(amt);
            action= "Player picked up "+std::to_string(amt);
            action +=" gold. ";
            player->move(str);
            grid[r][c] = player->getOrigin();
            player->setOrigin('.');
            grid[y][x] = '@';
            treasures.erase(treasures.begin()+at);
        }
        else{
            action += "Treasure cannot be picked. ";
        }
    }
    else{
        action += "Invalid movement";
    }
}

void Floor::playerUsePotion(std::string str){
    std::vector<int> pos = nextMove(str);
    int y = pos[0];
    int x = pos[1];
    if (grid[y][x] == 'P'){
        int at = potionAt(y, x);
        if (potions[at]->getType() != '0' || potions[at]->getType() != '3'){
            player->addPotion(potions[at]);
        }
        player->usePotion(potions[at]);
        std::string temp;
        switch(potions[at]->getType()){
        case 0:
            temp = "RH";
            break;
        
        case 1:
            temp = "BA";
            break;

        case 2:
            temp = "BD";
            break;
        
        case 3:
            temp = "PH";
            break;
                
        case 4:
            temp = "WA";
            break;
            
        case 5:
            temp = "WD";
            break;
        }
        action += "Player used potion " + temp;
        potions.erase(potions.begin()+at);
        grid[y][x] = '.';
    }
    else{
        action += "No potion in this direction. ";
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

