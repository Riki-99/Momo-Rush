#include "game.h"
#include "player.h"
#include <iostream>

int game::onGoing()
{
    if (gameState == 1) {
        timeRemaining = oneGameDuration - clk.getElapsedTime().asSeconds();
        if (p->dead || timeRemaining <= 0) {
            if (gameState != 2) {
                gameState = 2;
                endTimeSeconds = clk.getElapsedTime().asSeconds();
                timeRemaining = 0;
            }
        }
    }
    else if (gameState == 2) {
        if ((clk.getElapsedTime().asSeconds() - endTimeSeconds) > gap) {
            gameState = 0;
        }
    }
    return gameState;
}

game::game(Player& pl) : t1(text(f)), t2(text(f)), t3(text(f)), tempText(text(f)) {
    p = &pl;
    gameState = 0;
    clk.restart();
    if (!f.openFromFile("Assets/fonts/myfont.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }
}

void game::draw(rw& window)
{
    int state = onGoing();

    std::ostringstream oss1, oss2;
    oss1 << "Score : " << score;
    oss2 << "Time remaining : " << timeRemaining;

    t1.setString(oss1.str());
    t1.setCharacterSize(tilesize / 2);
    t1.setFillColor(sf::Color::White);
    t1.setStyle(sf::Text::Bold);

    t2.setCharacterSize(tilesize);
    t2.setFillColor(sf::Color::White);
    t2.setStyle(sf::Text::Bold);
    t2.setString("Game Over!");

    t3.setCharacterSize(tilesize / 1.5);
    t3.setFillColor(sf::Color::White);
    t3.setStyle(sf::Text::Bold);
    t3.setString(oss2.str());

    if (state == 1)
    {
        t1.setPosition({ static_cast<float>(tilesize * 14.5), 0.f });
        t3.setPosition({ tilesize * 6, tilesize * 1 });
        window.draw(t3);
    }
    else if (state == 2)
    {
        t2.setPosition({ tilesize * 6, tilesize * 3 });
        t1.setPosition({ static_cast<float>(tilesize * 7.5), tilesize * 5 });
        window.draw(t2);
    }
    if(state!=0)
    window.draw(t1);

    if (tempTextActive)
    {
        if (tempTextClock.getElapsedTime().asSeconds() < tempTextDuration)
        {
            window.draw(tempText);
        }
        else
        {
            tempTextActive = false;
        }
    }
}

void game::restart() {
    clk.restart();
    gameState = 1;
    score = 0;
    p->dead = false;
}

void game::drawText(const std::string& str, float duration)
{
    tempText.setString(str);
    tempText.setCharacterSize(tilesize / 2);
    tempText.setFillColor(sf::Color::White);
    tempText.setStyle(sf::Text::Bold);
    tempText.setPosition({ tilesize * 8.f, tilesize * 5.f });

    tempTextDuration = duration;
    tempTextClock.restart();
    tempTextActive = true;
}
