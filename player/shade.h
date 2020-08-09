#ifndef _SHADE_h_
#define _SHADE_h_

#include "../player.h"
#include "../enemy.h"

class Enemy;

class Shade: public Player{
    public:
    Shade();
    ~Shade() {}
    void accept(Enemy &) override;
    // void attack(std::shared_ptr <Enemy>) override;
};

#endif
