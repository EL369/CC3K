#include "floor.h"
#include <iostream>

Floor::Floor(std::vector<std::vector<char>> grid, int id):grid{grid},id{id}{
    // std::string line;
    // while(std::getline(ss, line)){
    //     std::vector<char> row;
    //     for(int j = 0; j<79; ++j) {
    //         row.emplace_back(line[j]);
    //     }
    //     grid.emplace_back(row);
    // }
    // std::cout<<"floor "<<id;
}


void Floor::print(){
    std::cout<<"!!!"<<std::endl;
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

