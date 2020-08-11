#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <vector>
#include <memory>
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
    std::string action = "Player enters the floor";

public:
    Floor( std::vector<std::vector<char>> grid, int id);

    ~Floor(){}

    std::shared_ptr<Player> getPlayer();
    std::vector<std::shared_ptr<Enemy>> getEnemies();
    std::vector<std::shared_ptr<Potion>> getPotions();
    std::vector<std::shared_ptr<Treasure>> getTreasures();
    std::vector<std::shared_ptr<Chamber>> getChambers();
    int getId();

    void print();

    void generateAll(std::shared_ptr<Player>);

    // generation
    void generateChambers();
    void generatePlayer(std::shared_ptr<Player>);
    void generatePotion(std::shared_ptr<Potion>);
    void generateTreasure(std::shared_ptr<Treasure>);
    void generateEnemy(std::shared_ptr<Enemy>);
    void generateStair();

    void erase(std::shared_ptr<Character>);
    void erase(std::shared_ptr<Potion>);
    void erase(std::shared_ptr<Treasure>);

    void move(std::shared_ptr<Character>, int, int, int, int);
    // void move(std::shared_ptr<Item>, int, int);

    // std::vector<int> getPos(int, int);

    // std::vector<int> existNear(char, int, int);

    void EnemymoveHelper(int);
    void Enemymove();

    //return true if there's an enemy in the current position
    int treasureAt(int row, int col);
    int potionAt(int row, int col);
    bool isRegularEnemy(int, int);
    int enemyAt(int, int);
    std::vector<int> nextMove(std::string);
    void enemyAttackMove();
    void playerAttack(std::string);
    void playerMove(std::string);
    void playerUsePotion(std::string);
};

#endif
