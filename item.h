#ifndef _ITEM_H_
#define _ITEM_H_
#include <iostream>
#include <vector>
#include <memory>

class Item{
protected:
    int row;
    int col;

public:
    Item(int, int);
    int getRow();
    int getCol();
    int setRow();
    int setCol();

};

#endif
