#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

#include "floor.h"
#include "player/shade.h"
#include "player.h"

std::string defaultFile ="cc3kfloor.txt";

std::vector<std::shared_ptr<Floor>> floors;

int main(int argc, char* argv[]) {
    std::ifstream file(defaultFile);
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
            // std::cout<<"--id---"<<id<<std::endl;
            ++id;
            row = 0;
        }
    }
    std::cout<<"Please choose your character: \ns for shade(defualt), d for drow, v for vampire, t for troll, g for goblin"<<std::endl;
    char playerChar;
    std::shared_ptr<Player> player;
    while (true){
        std::cin>>playerChar;
        if(playerChar == 's'){
            player = std::make_shared<Shade>();
            break;
        }
        //else if
        else{
            playerChar = 's';
            player = std::make_shared<Shade>();
            break;
        }
    }
    std::cout<<"Your character is: "<<playerChar<<std::endl;
    std::cout<<"Generating the floor..."<<std::endl;
    (floors[0])->generateAll(player);
    std::string cmd, arg;
    while (std::cin>>cmd){
        if(cmd == "no" || cmd== "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw"){
            (floors[0])->playerMove(cmd);
        }else if (cmd == "u"){
            std::cin>>arg;
            (floors[0])->playerUsePotion(arg);
        }else if (cmd == "a"){
            std::cin>>arg;
            (floors[0])->playerAttack(arg);
        }else{
            std::cout<<"invald command"<<std::endl;
        }floors[0]->print();
    }
}
