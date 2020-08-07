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
    ~Item() { }
    int getRow();
    int getCol();
    void setRow(int);
    void setCol(int);

};

#endif
