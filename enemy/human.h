#ifndef _HUMAN_h_
#define _HUMAN_h_

#include "../enemy.h"

class Human: public Enemy{
    public:
    Human(): Player{140,20,20,row,col,floorID, chamberID, maxHP} { }
};

#endif
 