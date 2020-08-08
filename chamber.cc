#include "chamber.h"
#include <stdlib.h>
#include "character.h"
#include "item.h"

Chamber::Chamber(int i, std::vector<std::vector<char>>& g):id{i}, grid{g}{
switch (id){
    case 0:
        topLeftX = 2;
        topLeftY = 2;
        width = 28;
        height = 6;
        break;
    case 1:
        topLeftX = 38;
        topLeftY = 2;
        width = 39;
        height = 12;
        break;
    case 2:
        topLeftX = 37;
        topLeftY = 9;
        width = 14;
        height = 5;
        break;
    case 3:
        topLeftX = 2;
        topLeftY = 14;
        width = 23;
        height = 9;
        break;
    case 4:
        topLeftX = 36;
        topLeftY = 15;
        width = 41;
        height = 8;
        break;
    }
}

//Generates the char in random position within range of this Chamber, returns the position
std::vector<int> Chamber::generateCharRand(char c){
    int x;
    int y;
    while(true){
        x = (rand() % width) + topLeftX;
        y = (rand() % height) + topLeftY;
        if (grid[x][y] == '.'){
            grid[x][y] = c;
            break;
        }
    }std::vector<int> pos;
    pos.emplace_back(x);
    pos.emplace_back(y);
    return pos;
}
void Chamber::erase(int x, int y){
    if(grid[x][y]!='-' && grid[x][y]!='|' && grid[x][y]!='+' && grid[x][y]!='#'){
        grid[x][y] = '.';
    }
}
char Chamber::getPos(int x, int y){
    return grid[x][y];
}

bool Chamber::inChamber(std::shared_ptr<Character> c){
    int row = c->getRow();
    int col = c->getCol();
    if(row >= topLeftX && col >= topLeftY && row < topLeftX+width && col < topLeftY+height){
        return true;
    }return false;
}

bool Chamber::inChamber(std::shared_ptr<Item> i){
    int row = i->getRow();
    int col = i->getCol();
    if(row >= topLeftX && col >= topLeftY && row < topLeftX+width && col < topLeftY+height){
        return true;
    }return false;
}
