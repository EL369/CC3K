
#ifndef _DWARF_h_
#define _DWARF_h_

#include "../enemy.h"

class Dwarf: public Enemy{
    friend class concreteType;
    public:
    Dwarf();
    void attackPlayer(Vampire &) override;
};

#endif
