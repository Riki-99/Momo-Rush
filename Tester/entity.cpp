#include "loader.h"
#include "entity.h"
#include "map.h"

Entity::Entity(int totalFramesPerAction, int frameSize) : Element(0, 0, 0, frameSize, frameSize, tiletxtr) {
    velocity = { 0,0 };
    acc = { 0.f,0.f };
    grounded = false;
    jumping = false;
    acc.y = gravity;
    currentState = idle;
    currentFrame = 0;
    dead = false;

    int stateCount = static_cast<int>(shielding) + 1;
    imgData.resize(stateCount);

    // populate idle (row 0) and running (row 1)
    for (int f = 0; f < totalFramesPerAction; ++f) {
        addImgData(static_cast<int>(idle), f, 0, frameSize, frameSize);
    }
    for (int f = 0; f < totalFramesPerAction; ++f) {
        addImgData(static_cast<int>(running), f, 2, frameSize, frameSize);
    }

    clk.restart();
}

void Entity::move(vec2f displacement, Map& m)
{
    currentState = idle;
    // compute which tiles we're testing against
    vec2i leftBlock = blockToLeft();   // {x-1, y}
    vec2i rightBlock = blockToRight(); // {x+1, y}
    vec2i downBlock = standingOn();    // {x, y+1}

    // Move to left if the tile to left is not solid and in bounds
    if (displacement.x < 0) {
        if (m.inBounds(leftBlock.y, leftBlock.x)) {
            if (!m.isSolid(leftBlock.y, leftBlock.x))
            {
                currentState = running;
                sprite.move({ displacement.x, 0 });
            }

        }
    }
    // Move to right if the tile to right is not solid
    else if (displacement.x > 0) {
        if (m.inBounds(rightBlock.y, rightBlock.x)) {
            if (!m.isSolid(rightBlock.y, rightBlock.x))
            {
                currentState = running;
                sprite.move({ displacement.x, 0 });
            }
        }
    }

    // If positive y displacement, falling down
    if (displacement.y > 0)
    {
        // If block below is solid, the player is grounded and not jumping
        if (m.inBounds(downBlock.y, downBlock.x) && m.isSolid(downBlock.y, downBlock.x))
        {
            grounded = true;
            jumping = false;
            // snap to top of tile to avoid passing through
            float snapY = downBlock.y * tilesize - hitbox.size.y; // top of block minus height
            setPosition({ sprite.getPosition().x, snapY });
        }
        else {
            sprite.move({ 0, displacement.y });
        }
    }
    else if (displacement.y < 0)
    {
        sprite.move({ 0, displacement.y });
    }

}



// Returns the tile the entity is standing on
vec2i Entity::standingOn() {
    //Standing on tile of xth index and y+1th index
    // Taking average of the hitbox to determine if falling
    return { static_cast<int>(std::floor((hitbox.position.x + hitbox.size.x / 2) / tilesize)), static_cast<int>(std::floor((hitbox.position.y) / tilesize + 1)) };
}

// Returns the tile to the left of the entity
vec2i Entity::blockToLeft() {
    return { static_cast<int>(std::floor((hitbox.position.x + hitbox.size.x / 3) / tilesize)), static_cast<int>(std::floor(hitbox.position.y / tilesize)) };
}

// Returns the tile to the right of the entity
vec2i Entity::blockToRight() {
    return { static_cast<int>(std::ceil((hitbox.position.x - hitbox.size.x / 3) / tilesize)), static_cast<int>(std::floor(hitbox.position.y / tilesize)) };
}

void Entity::addImgData(int idx, int frameCol, int frameRow, int sX, int sY) {
    if (idx < 0) return;
    if (imgData.size() <= idx) {
        imgData.resize(idx + 1);
    }
    imgData[idx].push_back(imageData(frameCol, frameRow, sX, sY));
}

void Entity::animate() {
    int stateIdx = static_cast<int>(currentState);
    if (stateIdx < 0 || stateIdx >= static_cast<int>(imgData.size())) return;
    if (imgData[stateIdx].empty()) return;

    if (clk.getElapsedTime().asSeconds() >= oneFrameDuration)
    {
        currentFrame++;
        if (currentFrame >= imgData[stateIdx].size())
        {
            currentFrame = 0;
        }
        imageData& imdata = imgData[stateIdx][currentFrame];
        sprite.setTextureRect(intrect({ imdata.xCoords, imdata.yCoords }, { imdata.sizeX, imdata.sizeY }));
        clk.restart();
    }
}