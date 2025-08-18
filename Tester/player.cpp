#include "player.h";
#include "loader.h";
#include "map.h";
#include "game.h"

Player::Player(int i, int x, int y, int w, int h) : Element(i, x, y, w, h, TextureList<Player>::getTexture(i)), Entity(6, 56) {
    health = 10;
    movementSpeed = 1.2;
}


void Player::update(Map& m, game &g)
{
    horizontalMotion(m);
    if (abs(acc.x) > frictionCoeff)
    {
        if (acc.x < 0)
        {
            velocity.x = acc.x + frictionCoeff;
        }
        else if (acc.x > 0) {
            velocity.x = acc.x - frictionCoeff;
        }
    }
    else {
        acc.x = 0;
        velocity.x = 0;
    }
    checkJump();
    velocity.y += acc.y;
    move({ velocity.x * timeUnit, velocity.y * timeUnit }, m);
    animate();
    hitbox = sprite.getGlobalBounds();
    checkCollisionWithObstacle(m, g);
}


void Player::horizontalMotion(Map& m) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        acc.x = -movementSpeed;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        acc.x = +movementSpeed;
    }
    else {
        if (acc.x < 0)
        {
            acc.x += 0.1 * movementSpeed;
        }

        else if (acc.x > 0)
        {
            acc.x -= 0.1 * movementSpeed;
        }
    }
}
void Player::checkJump()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        if (!jumping and grounded)
        {
            velocity.y = -jumpHeight;
            jumping = true;
            grounded = false;
        }
    }
}

void Player::draw(rw& window) {
    // fix player at this many tiles from the left of the screen
    const int playerScreenTileX = 7;
    vec2f currentPos = sprite.getPosition();
    // Set player's on-screen X to playerScreenTileX * tilesize (keep Y unchanged)
    sprite.setPosition({ static_cast<float>(playerScreenTileX * tilesize), currentPos.y });
    // When drawing player, we pass cameraOffset = 0 because player's position is already in screen space
    Element::draw(window, 0.f);
    sprite.setPosition(currentPos);
}

void Player::checkCollisionWithObstacle(Map& m, game& g)
{
    vec2i block_below = standingOn();

    // check 3x3 neighborhood but only react to index == 4 there
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            Tile& tile = m.getTile(block_below.y + dy, block_below.x + dx);
            if (tile.index != 4) continue;

            floatrect tilehbox = tile.getHitBox();
            if (hitbox.findIntersection(tilehbox)) {
                if (!tile.consumed) {
                    tile.consumed = true;
                    g.incrementScore();
                    sf::Sound(s2).play();
                }
            }
        }
    }

    // check only the current tile for traps and any other collisions
    Tile& current = m.getTile(block_below.y, block_below.x);
    floatrect currenthbox = current.getHitBox();
    if (hitbox.findIntersection(currenthbox)) {
        if (current.trap) {
            dead = true;
            return;
        }
        else if (current.index == 4 && !current.consumed) {
            current.consumed = true;
            g.incrementScore();
            sf::Sound(s2).play();
        }
    }
}

