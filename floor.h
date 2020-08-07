#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Player;
class Enemy;
class Potion;
class Treasure;
class Chamber;
class Character;

class Floor{
private:
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Potion>> potions;
    std::vector<std::shared_ptr<Treasure>> treasures;
    std::vector<std::shared_ptr<Chamber>> chambers;
    std::vector<std::vector<char>> grid;
    int id;

public:
    Floor( std::vector<std::vector<char>> grid, int id);

    std::shared_ptr<Player> getPlayer();
    std::vector<std::shared_ptr<Enemy>> getEnemies();
    std::vector<std::shared_ptr<Potion>> getPotions();
    std::vector<std::shared_ptr<Treasure>> getTreasures();
    std::vector<std::shared_ptr<Chamber>> getChambers();

    void print();

    void update();

    void generateChamber();

    void generateRand(std::shared_ptr<Player>);
    void generateRand(std::shared_ptr<Potion>);
    void generateRand(std::shared_ptr<Treasure>);
    void generateRand(std::shared_ptr<Enemy>);
    void generateRand( char stair );

    void erase(std::shared_ptr<Character>);
    void erase(std::shared_ptr<Potion>);
    void erase(std::shared_ptr<Treasure>);

    void add(std::shared_ptr<Character>, int, int);
    void add(std::shared_ptr<Treasure>, int, int);
    void add(std::shared_ptr<Potion>, int, int);

    bool inChamber(std::shared_ptr<Character>);
    bool inChamber(std::shared_ptr<Treasure>);
    bool inChamber(std::shared_ptr<Potion>);

};

#endif
