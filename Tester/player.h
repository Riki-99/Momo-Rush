#pragma once
#include "global.h"
#include "entity.h"
#include "map.h"
class Player : public Entity {
private:
    const float jumpHeight = 0.9f;
public:
    Player(int i, int x, int y, int w, int h, int s);
    // Updates the entity
    void update(Map& m);

    // Deals with moving left or right
    void horizontalMotion(Map& m);

    // Deals with pressing space
    void checkJump();

    // Draws the player entity at the (almost) center of the screen
    void draw(rw& window);
};