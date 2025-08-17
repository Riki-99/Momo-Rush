#include "game.h"
#include "player.h"
int game::onGoing()
{
    if (p->dead)
    {
        return 0;
    }
    if (clk.getElapsedTime().asSeconds() >= oneGameDuration)
    {
        return 0;
    }
    return 1;
}

game::game(Player& pl) {
    p = &pl;
    gameState = 1;
    clk.restart();
}