#pragma once
#include "global.h"
#include <iostream>
#include <fstream>
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
        sprite.setScale({ static_cast<float>(gd::tilesize/ size), static_cast<float>(gd::tilesize/ size) });
        hitbox = sprite.getGlobalBounds();
        //setPosition({ 5 * gd::tilesize, 5 * gd::tilesize });
    }
     // Set position using absolute value
     void setPosition(vec2f position) {
         sprite.setPosition(position);
         hitbox = sprite.getGlobalBounds();
     }
     // Set on tiles
     void setOnTile(int tileX, int tileY)
     {
         setPosition({ tileX * gd::tilesize, tileY * gd::tilesize });

     }

     // Draw on a sf::RenderWindow
    void draw(rw& window) {

        window.draw(sprite);
    }

    floatrect getHitBox() {
        return hitbox;
    }
};


class Entity : virtual public Element {
    int health;
    vec2f velocity;
    const int timeUnit = 1;
public:
    virtual void update() = 0;
};

class Player : public Entity{
private:
    int health;
    vec2f velocity;
    const int timeUnit = 1;
public:
    Player(int i, int x, int y, int w, int h, int s): Element(i,x,y,w,h,s,TextureList<Player>::getTexture(i)){
        health = 10;
        velocity = { 0,0 };
}
    void update()
    {
        sprite.move({ velocity.x * timeUnit, velocity.y *timeUnit});
    }
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

extern Txt tiletxtr;
class Tile : public Element
{
public:
    // Index of the tile used.
    int index;
    Tile(int i, int x, int y, int w, int h, int s) : Element(i, x, y, w, h, s, TextureList<Tile>::getTexture(i)) { index = i;}
    Tile() : Element(0, 0, 0, 0, 0, 0, tiletxtr) { index = 0;}
};
class Map
{
     const int rows = 10;
     const int cols = 100;
     // a 2d vector for configuring all the tiles 
     std::vector < std::vector<Tile>> tiles;

public:
    // Setting the dimensions of rows and cols in runtime, initializing rows number of Tile vectors that contains yet another tile cols number of Tile vectors
    Map(str s): tiles(rows) {
        int tmp;
        std::ifstream file(s);
        int colCt = cols;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                file >> tmp;
                switch (tmp) 
                {
                case 0:
                    tiles[i].push_back(Tile(0, 4, 0, 1, 1, 24));
                    break;
                case 1:
                    tiles[i].push_back(Tile(0, 12, 0, 1, 1, 24));
                    break;
                case 2:
                    tiles[i].push_back(Tile(0, 10, 0, 1, 1, 24));
                    break;
                case 3:
                    tiles[i].push_back(Tile(0, 15, 0, 1, 1, 24));
                    break;
                case 4:
                    tiles[i].push_back(Tile(0, 0, 11, 1, 1, 24));
                }
                // setontile(j,i) because we use the distance from the absolute left, j being the distance from the horizontal axix and i being the disntace from the vertical axis.
                tiles[i][tiles[i].size()-1].setOnTile(j, i);
            }
        }
    }

    void  draw(rw& window) {
        for (int i = 0; i < tiles.size(); i++)
        {
            for (int j = 0; j < tiles[0].size(); j++)
            {
                tiles[i][j].draw(window);
            }
        }
   }
};

