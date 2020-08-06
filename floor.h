#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
class Player;
class Enemy;
class Potion;
class Treasure;
class Chamber;

class Floor{
private:
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Potion>> potions;
    std::vector<std::shared_ptr<Treasure>> treasures;
    std::vector<std::shared_ptr<Chamber>>chambers;

public:
    int readFile(std::fstream &);
    std::shared_ptr<Player> getPlayer();
    std::vector<std::shared_ptr<Enemy>> getEnemies();
    std::vector<std::shared_ptr<Potion>> getPotions();
    std::vector<std::shared_ptr<Treasure>> getTreasures();
    std::vector<std::shared_ptr<Chamber>> getChambers();
    std::ostream print();
    void update();

};

#endif
