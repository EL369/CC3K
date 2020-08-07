#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <memory>
class Gold;

class Character{
private:
    int health;
    int attack;
    int defense;
    int row;
    int col;
    std::shared_ptr<Gold> gold;

public:
    Character(int, int, int, int, std::shared_ptr<Gold>);
    int getHP();
    int getAtk();
    int getDF();
    int getGold();
    int getRow();
    int getCol();
    void addRow(int);
    void addCol(int);
    void addHP(int);
    void addAttack(int);
    void addDefense(int);

};
#endif
