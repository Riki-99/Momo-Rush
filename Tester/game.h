#pragma once
#include "loader.h"
#include "global.h"
// In order to write into strings
#include <sstream>

class Player;

class game {
    // 0 means ended, 1 means on going
    int gameState;
    int score = 0;
    Clock clk;
    Player* p;
    font f;
    const int oneGameDuration = 60;
    text t1, t2, t3;
    int timeRemaining;
public:
    int onGoing();
    game(Player& pl);

    void incrementScore() {
        score++;
    }
    void draw(rw& window)
    {
        ostringstream oss1, oss2;
        oss1 << "Score : " << score;
        oss2 << "Time remaining : " << timeRemaining;
        t1.setString(oss1.str());
        t1.setCharacterSize(tilesize/2);
        t1.setFillColor(sf::Color::White);
        t1.setStyle(sf::Text::Bold);
        t1.setString(oss1.str());
        t2.setCharacterSize(tilesize);
        t2.setFillColor(sf::Color::White);
        t2.setStyle(sf::Text::Bold);
        t2.setString("Game Over!");

        t3.setCharacterSize(tilesize/1.5);
        t3.setFillColor(sf::Color::White);
        t3.setStyle(sf::Text::Bold);
        t3.setString(oss2.str());

        if (onGoing())
        {
            t1.setPosition({ static_cast<float>(tilesize * 14.5), 0.f });
            t3.setPosition({ tilesize * 6, tilesize * 1 });
            window.draw(t3);
        }
        else
        {
            t2.setPosition({ tilesize * 6, tilesize * 3 });
            t1.setPosition({ static_cast<float>(tilesize *7.5), tilesize* 5});
            window.draw(t2);
        }
        window.draw(t1);
    }

    void restart();
};