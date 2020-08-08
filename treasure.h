#ifndef _TREASURE_H_
#define _TREASURE_H_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "item.h"

class Treasure: public Item{
    int amount;
    bool pick;

    public:
    Treasure(int, int, int);
    ~Treasure() { }
    int getAmt();
    bool getPick();
    void setAmt(int);
    void setPick(bool);
};

#endif
