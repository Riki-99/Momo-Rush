#include "player.h";
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
            cout << "Jump invoked" << endl;
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