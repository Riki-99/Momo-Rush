#include "game.h"
#include "player.h"
int game::onGoing()
{
    timeRemaining = 60 - clk.getElapsedTime().asSeconds();
    if (p->dead)
    {
        gameState = 0;
    }
    if (timeRemaining <= 0)
    {
        gameState = 0;
    }
    return gameState;
}

game::game(Player& pl): t1(text(f)), t2(text(f)), t3(text(f)){
    p = &pl;
    gameState = 0;
    clk.restart();
    if (!f.openFromFile("Assets/fonts/myfont.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }
}
void game::restart() {
    clk.restart();
    gameState = 1;
    p->dead = false;
}