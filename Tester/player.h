#pragma once
#include "global.h"
#include "entity.h"
#include "map.h"
class Player : public Entity {
private:
    const float jumpHeight = 1.f;
public:
    Player(int i, int x, int y, int w, int h);
    // Updates the entity
    void update(Map& m);

    // Deals with moving left or right
    void horizontalMotion(Map& m);

    // Deals with pressing space
    void checkJump();

    // Draws the player entity at the (almost) center of the screen
    void draw(rw& window);

    void checkCollisionWithObstacle(Map& m) {
        vec2i block_below = standingOn();
        Tile tile_below = m.getTile(block_below.y, block_below.x);
        Tile this_tile = m.getTile(block_below.y - 1, block_below.x);
        Tile tile_to_left = m.getTile(block_below.y - 1, block_below.x - 1);
        Tile tile_to_right = m.getTile(block_below.y - 1, block_below.x + 1);
        // Bottom
        floatrect downtilehbox = tile_below.getHitBox();
        floatrect lefttilehbox = tile_to_left.getHitBox();
        floatrect righttilehbox = tile_to_right.getHitBox();
        floatrect currenttilehbox = this_tile.getHitBox();
        // l
        if ((hitbox.findIntersection(downtilehbox) && tile_below.trap) || (hitbox.findIntersection(lefttilehbox) && tile_to_left.trap) || (hitbox.findIntersection(righttilehbox) && tile_to_right.trap))
        {
            dead = true;
        }
    }
};