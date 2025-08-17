#pragma once
#include "global.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

// A template for storing all textures in vectors because we need to load the mininal amount of textures possible and reuse them for creating sprites
template <class T>
class TextureList{
private:
    // Inline because without using inline, this templated class would not be definted but only declared because of the templatization
    inline static std::vector<Txt>  texture;
public:
    // Member function to get the texture of this static class belonging to the specified index of the vector stored in it.
    static Txt& getTexture(int idx)
    {
        return texture[idx];
    }
    // Adding a new texture whose path is passed as argument
    static void addTexture(str s)
    {
        texture.push_back(Txt(s));
    }
    friend void loadAllTextures();
};
// A function to load all textures
void loadAllTextures();

// A class to store data of individual sprite data 
struct imageData {
    int xCoords;
    int yCoords;
    int size;
    imageData(int xIdx, int yIdx, int siz) : xCoords(xIdx* siz), yCoords(yIdx* siz), size(siz) {}
};
// A class that serves as blueprint for all objects that will be of the tile size.
class Element {
protected:
    floatrect hitbox;
    Sprt sprite;
public:
    // Setting up the cons  tructor, no default constructor;
    Element(int index, int xthIdx, int ythIdx, int width, int height, int size, Txt& ref);

    // Set position using absolute value
    void setPosition(vec2f position);

    // Set on tiles (world coords)
    void setOnTile(int tileX, int tileY);

    // Draw on a sf::RenderWindow
    // cameraOffsetPx = how many pixels the world should be shifted to the left (actual x - x coordinates of the player)
    void draw(rw& window, float cameraOffsetPx);

    floatrect getHitBox();
};

extern Txt tiletxtr;


class Background {
private:
    Sprt sprite;
public:
    Background(int index) : sprite(TextureList<Background>::getTexture(index)) {
        vec2f localBounds = sprite.getLocalBounds().size;
        sprite.setScale({ desktop.size.x / localBounds.x, desktop.size.y / localBounds.y });
    }
    void draw(rw& window) {
        window.draw(sprite);
    }
};
class Enemy;
