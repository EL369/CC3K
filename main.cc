#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

#include "floor.h"

std::string defaultFile ="cc3kfloor.txt";

std::vector<std::shared_ptr<Floor>> floors;

int main(int argc, char* argv[]) {
    std::ifstream file(defaultFile);
    std::cout<<"???"<<argc;
    if (argc > 1) {
        std::ifstream file(argv[1]);
        if(!file.good()){
            std::cout<<"File is invalid.";
            exit(1);
        }
    }
    std::vector<std::vector<char>> grid;
    std::string s;
    std::vector<char> line;
    int id = 0;
    int row = 0;
    int col = 79;
    while (std::getline(file, s)){
        for(int i=0; i<col; ++i){
            line.emplace_back(s[i]);            
            // std::cout<<"---char---"<<line[i]<<std::endl;

        }grid.emplace_back(line);
        ++row;
        s = "";
        line.clear();
        if(row==25){
            floors.emplace_back(std::make_shared<Floor>(grid, id));
            std::cout<<"--id---"<<id<<std::endl;
            ++id;
            row = 0;
        }
    }(floors[0])->print();
}
