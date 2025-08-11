#pragma once
#include "global.h"
#include <iostream>
#include <vector>
// A template for storing all textures in vectors because we need to load the mininal amount of textures possible and reuse them for creating sprites
template <class T>
class TextureList {
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

// A class that serves as blueprint for all objects that will be of the tile size.
class Element {
protected:
    Sprt sprite;
    floatrect hitbox;

public:
    // Setting up the constructor, no default constructor;
     Element(int index, int xthIdx, int ythIdx, int width, int height, int size, Txt&  ref): sprite(ref){
        sprite.setTextureRect(intrect(
            { xthIdx * size, ythIdx * size },
            { size * width, size * height }
        ));
        sprite.setScale({ static_cast<float>(gd::tilesize*2/ size), static_cast<float>(gd::tilesize*2/ size) });
        hitbox = sprite.getGlobalBounds();
    }

    void draw(rw& window) {
        window.draw(sprite);
    }
};

class Player : public Element {
private:
    int health;

public:
    Player(int i, int x, int y, int w, int h, int s): Element(i,x,y,w,h,s,TextureList<Player>::getTexture(i)){}
};

class Background{
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
class Tile;
class Map;

