//#include "enemy.h"
//#include "loader.h" // if you have TextureList<Enemy>, used in Element constructor
//#include <iostream>
//
//// Construct the Element part with a texture from your TextureList (matches Player pattern).
//Enemy::Enemy(int textureIndex, int x, int y, int w, int h, Player* targetPtr)
//    : Element(textureIndex, x, y, w, h, TextureList<Enemy>::getTexture(textureIndex))
//    , Entity(6, 56) // totalFramesPerAction, frameSize (match your Entity usage)
//    , target(targetPtr)
//{
//    health = 3;
//    movementSpeed = chaseSpeed;
//    acc.y = gravity;
//    dead = false;
//
//    clk.restart();
//    attackClock.restart();
//    // set initial sprite position to provided x,y (Element likely already does this — set again to be safe)
//    sprite.setPosition({ static_cast<float>(x), static_cast<float>(y) });
//    hitbox = sprite.getGlobalBounds();
//}
//
//void Enemy::thinkAndMoveTowardPlayer(Map& m)
//{
//    currentState = idle;
//    if (!target || target->dead) {
//        // slow to a stop
//        if (acc.x < 0) acc.x += 0.1f * chaseSpeed;
//        else if (acc.x > 0) acc.x -= 0.1f * chaseSpeed;
//        return;
//    }
//
//    vec2i myBlock = standingOn();
//    vec2i playerBlock = target->standingOn();
//
//    if (playerBlock.x < myBlock.x) {
//        acc.x = -chaseSpeed;
//        currentState = running;
//    }
//    else if (playerBlock.x > myBlock.x) {
//        acc.x = +chaseSpeed;
//        currentState = running;
//    }
//    else {
//        // same column: ease to stop
//        if (acc.x < 0) acc.x += 0.1f * chaseSpeed;
//        else if (acc.x > 0) acc.x -= 0.1f * chaseSpeed;
//    }
//}
//
//void Enemy::tryAttackPlayer()
//{
//    if (!target || target->dead) return;
//
//    vec2i myBlock = standingOn();
//    vec2i playerBlock = target->standingOn();
//
//    bool closeHoriz = std::abs(myBlock.x - playerBlock.x) <= 1;
//    bool sameLevel = std::abs(myBlock.y - playerBlock.y) <= 1;
//
//    if (closeHoriz && sameLevel) {
//        if (attackClock.getElapsedTime().asSeconds() >= attackCooldownSec) {
//            // Right now player cannot retaliate: mark player dead or apply damage
//            std::cout << "Enemy attacked player\n";
//            target->dead = true;
//            attackClock.restart();
//        }
//    }
//}
//
//void Enemy::update(Map& m)
//{
//    if (dead) return;
//
//    // decide movement
//    thinkAndMoveTowardPlayer(m);
//
//    // friction integration (same logic as Player)
//    if (std::abs(acc.x) > frictionCoeff) {
//        if (acc.x < 0) velocity.x = acc.x + frictionCoeff;
//        else velocity.x = acc.x - frictionCoeff;
//    }
//    else {
//        acc.x = 0.f;
//        velocity.x = 0.f;
//    }
//
//    // gravity
//    velocity.y += acc.y;
//
//    // move with tile collision logic in Entity::move
//    move({ velocity.x * timeUnit, velocity.y * timeUnit }, m);
//
//    // animate sprite
//    animate();
//
//    // update hitbox
//    hitbox = sprite.getGlobalBounds();
//
//    // attempt attack
//    tryAttackPlayer();
//}
