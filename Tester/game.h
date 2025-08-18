#pragma once
#include "loader.h"
#include "global.h"
#include <sstream>

class Player;

class game {
    int gameState;
    int score = 0;
    const int gap = 3;
    Clock clk;
    Player* p;
    font f;
    const int oneGameDuration = 60;
    text t1, t2, t3;
    int timeRemaining;
    float endTimeSeconds = 0.f;

    text tempText;
    Clock tempTextClock;
    float tempTextDuration = 0;
    bool tempTextActive = false;

public:
    int onGoing();
    game(Player& pl);

    void incrementScore() { score++; }
    void draw(rw& window);

    void restart();
    void drawText(const std::string& str, float duration);
};
