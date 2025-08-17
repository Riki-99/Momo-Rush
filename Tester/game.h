#pragma once
#include "loader.h"
#include "global.h"

class Player;

class game {
    // 0 means ended, 1 means on going
    int gameState;
    int score = 0;
    Clock clk;
    Player* p;
    int oneGameDuration = 60;
public:
    int onGoing();
    game(Player& pl);

    void incrementScore() {
        score++;
    }

    void draw(rw& window)
    {

    }
};