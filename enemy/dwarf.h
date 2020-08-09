
#ifndef _DWARF_h_
#define _DWARF_h_

#include "../enemy.h"

class Dwarf: public Enemy{
    friend class concreteLevel;
    public:
    Dwarf(): Enemy{100,20,30,0,0,false} { }
};

#endif
