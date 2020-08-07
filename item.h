#ifndef _ITEM_H_
#define _ITEM_H_
#include <iostream>
#include <vector>
#include <memory>

class Item{
private:
    int row;
    int col;

public:
    int getRow();
    int getCol();
    int setRow();
    int setCol();

};

#endif
