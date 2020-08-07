#ifndef _SHADE_h_
#define _SHADE_h_

#include "../player.h"

class Shade: public Player{
    public:
    Shade(): Player{125,25,25,row,col,floorID, chamberID, 125} { }
    ~Shade() override {}
};

#endif
