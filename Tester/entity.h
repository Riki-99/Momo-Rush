#pragma once
#include "global.h"
#include "loader.h"
#include "map.h"
#include "game.h"

class Entity : virtual public Element {
protected:
    int health;
    vec2f velocity;
    Clock clk;
    vec2f acc;
    const float frictionCoeff = 0.5f;
    const int timeUnit = 1;
    const float gravity = 0.003f;
    bool grounded, jumping;
    float movementSpeed;
    float oneFrameDuration = 0.1f;
    vector <vector <imageData>> imgData;
    // Different states an entity can be in such as standing still, running, attacking ,jumping etc.
    enum states { idle, attack, running, jumpin, landing, beingdamaged, dying, sixfeetunder, spellcast, crouch, shielding };
    states currentState;
    // Which frame among the states
    int currentFrame;
public:
    bool dead;
    Entity(int totalFramesPerAction, int frameSize);
    virtual void update(Map& m, game& g) = 0;
    void move(vec2f displacement, Map& m);

    // Returns the tile the entity is standing on
    vec2i standingOn();

    // Returns the tile to the left of the entity
    vec2i blockToLeft();

    // Returns the tile to the right of the entity
    vec2i blockToRight();

    // Adds image data to the ImageData class which then creates an int rect that can be used to crop out individual sprites from the sprite sheet
    void addImgData(int idx, int frameCol, int frameRow, int sX, int sY);

    void animate();
};