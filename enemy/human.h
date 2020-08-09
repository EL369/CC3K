#ifndef _HUMAN_h_
#define _HUMAN_h_

#include "../enemy.h"

class Human: public Enemy{
    friend class concreteLevel;
    public:
    Human();
};

#endif
