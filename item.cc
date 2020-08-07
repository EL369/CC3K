#include "item.h"

Item::Item(int row, int col):
    row{row}, col{col} { }

int Item::getRow(){
    return row;
}

int Item::getCol(){
    return col;
}

void Item::setRow(int r){
    this->row = r;
}

void Item::setCol(int c){
    this->col = c;
}
