#ifndef _NORMAL_h_
#define _NORMAL_h_

#include "../treasure.h"

class Normal: public Treasure{
    public:
    Normal(): Treasure{0, 0, 2, 1} { }
};

#endif
