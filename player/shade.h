#ifndef _SHADE_h_
#define _SHADE_h_

#include "../player.h"

class Shade: public Player{
    public:
    Shade();
    ~Shade() {}
    void accept(std::shared_ptr <Enemy>) override;
    // void attack(std::shared_ptr <Enemy>) override;
};

#endif
