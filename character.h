#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <memory>
class Gold;

class Character{
protected:
    int health;
    int attack;
    int defense;
    int row;
    int col;

public:
    Character(int, int, int, int, int);
    virtual ~Character() { }
    int getHP();
    int getAtk();
    int getDF();
    int getRow();
    int getCol();
    void moveRow(int);
    void moveCol(int);
    void addAtk(int);
    void addDF(int);
    void addHP(int);
    void setRow(int);
    void setCol(int);

};
#endif
