#pragma once

#include "global.h"
#include "entity.h"
#include "map.h"
#include "player.h"
#include <cmath>
#include <iostream>

// Simple Enemy implemented inline to avoid linker issues while integrating.
// Constructor signature exactly: Enemy(int textureIndex, int x, int y, int w, int h, Player* target)
class Enemy : public Entity {
public:
    Enemy(int textureIndex, int x, int y, int w, int h, Player* target)
        // Because Entity virtually inherits Element, the most-derived must initialize Element:
        : Element(textureIndex, x, y, w, h, tiletxtr) // use tiletxtr to avoid depending on TextureList
        , Entity(6, 56)
        , target(target)
    {
        health = 3;
        movementSpeed = 0.9f;
        acc.y = gravity;
        dead = false;
        clk.restart();
        attackClock.restart();
        sprite.setPosition({ static_cast<float>(x), static_cast<float>(y) });
        hitbox = sprite.getGlobalBounds();
    }

    // Override Entity's pure virtual update
    void update(Map& m) override
    {
        if (dead) return;

        // Decide horizontal movement
        thinkAndMoveTowardPlayer(m);

        // Friction integration (same as Player)
        if (std::abs(acc.x) > frictionCoeff)
        {
            if (acc.x < 0) velocity.x = acc.x + frictionCoeff;
            else velocity.x = acc.x - frictionCoeff;
        }
        else {
            acc.x = 0.f;
            velocity.x = 0.f;
        }

        // Gravity
        velocity.y += acc.y;

        // Use Entity::move for tile collisions
        move({ velocity.x * timeUnit, velocity.y * timeUnit }, m);

        // Animate and refresh hitbox
        animate();
        hitbox = sprite.getGlobalBounds();

        // Try attack
        tryAttackPlayer();
    }

    void draw(rw& window, float cameraOffsetX = 0.f)
    {
        Element::draw(window, cameraOffsetX);
    }

private:
    Player* target = nullptr;
    sf::Clock attackClock;
    float attackCooldownSec = 1.0f;
    float chaseSpeed = 0.9f;

    void thinkAndMoveTowardPlayer(Map& /*m*/)
    {
        currentState = idle;
        if (!target || target->dead) {
            if (acc.x < 0) acc.x += 0.1f * chaseSpeed;
            else if (acc.x > 0) acc.x -= 0.1f * chaseSpeed;
            return;
        }

        vec2i myBlock = standingOn();
        vec2i playerBlock = target->standingOn();

        if (playerBlock.x < myBlock.x) {
            acc.x = -chaseSpeed;
            currentState = running;
        }
        else if (playerBlock.x > myBlock.x) {
            acc.x = +chaseSpeed;
            currentState = running;
        }
        else {
            if (acc.x < 0) acc.x += 0.1f * chaseSpeed;
            else if (acc.x > 0) acc.x -= 0.1f * chaseSpeed;
        }
    }

    void tryAttackPlayer()
    {
        if (!target || target->dead) return;

        vec2i myBlock = standingOn();
        vec2i playerBlock = target->standingOn();

        bool closeHoriz = std::abs(myBlock.x - playerBlock.x) <= 1;
        bool sameLevel = std::abs(myBlock.y - playerBlock.y) <= 1;

        if (closeHoriz && sameLevel) {
            if (attackClock.getElapsedTime().asSeconds() >= attackCooldownSec) {
                std::cout << "Enemy attacked player\n";
                target->dead = true;
                attackClock.restart();
            }
        }
    }
};
