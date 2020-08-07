#include "floor.h"
#include <iostream>

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

