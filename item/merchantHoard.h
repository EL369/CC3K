#ifndef _MERCHANTHOARD_h_
#define _MERCHANTHOARD_h_

#include "../treasure.h"

class Mhoard: public Treasure{
    public:
    Mhoard(): Treasure{0, 0, 4, 2} { }
};


#endif
