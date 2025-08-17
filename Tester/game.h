#pragma once
#include "loader.h"
#include "global.h"
#include "player.h"

class game {
    // 0 means ended, 1 means on going
    int gameState;
    Player* p;
public:
    int onGoing()
    {
        if (p->dead)
        {
            return 0;
        }
        return 1;
    }
    game(Player& pl) {
        p = &pl;
        gameState = 1;
    }
};