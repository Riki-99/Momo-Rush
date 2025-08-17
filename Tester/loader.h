#pragma once
#include "global.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

extern sf::SoundBuffer s1;
extern sf::SoundBuffer s2;
extern sf::SoundBuffer s3;
extern sf::Music s4;
extern sf::Music s5;

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
    int sizeX;
    int sizeY;
    imageData(int xIdx, int yIdx, int siz1, int siz2) : xCoords(xIdx* siz1), yCoords(yIdx* siz2), sizeX(siz1), sizeY(siz2) {}
    imageData() { sizeY = sizeX = yCoords = xCoords = 0; }
};
// A class that serves as blueprint for all objects that will be of the tile size.
class Element {
protected:
    floatrect hitbox;
    Sprt sprite;
public:
    // Setting up the cons  tructor, no default constructor;
    Element(int index, int xthIdx, int ythIdx, int width, int height, Txt& ref);

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
        sprite.setScale({ desktop.x / localBounds.x, desktop.y / localBounds.y });
    }
    void draw(rw& window) {
        window.draw(sprite);
    }
};
class Enemy;