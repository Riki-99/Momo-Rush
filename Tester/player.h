#pragma once
#include "global.h"
#include "entity.h"
#include "map.h"
#include "game.h"

class Player : public Entity {
private:
    const float jumpHeight = 1.f;
public:
    Player(int i, int x, int y, int w, int h);
    // Updates the entity
    void update(Map& m, game& g);

    // Deals with moving left or right
    void horizontalMotion(Map& m);

    // Deals with pressing space
    void checkJump();

    // Draws the player entity at the (almost) center of the screen
    void draw(rw& window);

    void checkCollisionWithObstacle(Map& m, game& g);

};