#pragma once
#include "global.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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
    floatrect hitbox;

public:
    Sprt sprite;
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

extern Txt tiletxtr;
class Tile : public Element
{
public:
    // Index of the tile used.
    int index;
    bool solid;
    Tile(int i, int x, int y, int w, int h, int s, int c) : Element(i, x, y, w, h, s, TextureList<Tile>::getTexture(i)) { index = c; solid = bool(index); }
    Tile() : Element(0, 0, 0, 0, 0, 0, tiletxtr) { index = 0; solid = bool(index); }
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
                    tiles[i].push_back(Tile(0, 4, 0, 1, 1, 24, 0));
                    break;
                case 1:
                    tiles[i].push_back(Tile(0, 12, 0, 1, 1, 24, 1));
                    break;
                case 2:
                    tiles[i].push_back(Tile(0, 10, 0, 1, 1, 24, 2));
                    break;
                case 3:
                    tiles[i].push_back(Tile(0, 15, 0, 1, 1, 24, 3));
                    break;
                case 4:
                    tiles[i].push_back(Tile(0, 0, 11, 1, 1, 24, 4));
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
    // Returns tile at map.tiles[i][j]
    Tile& getTile(int i, int j)
    {
        return tiles[i][j];
    }
};


class Entity : virtual public Element {
protected:
    int health;
    vec2f velocity;
    const int timeUnit = 1;
    const int fallVelocity = 1;
public:
    virtual void update(Map& m) = 0;
    void move(vec2f displacement)
    {
        //std::cout << "Vel : " << velocity.x << " " << velocity.y << std::endl;
        sprite.move(displacement);
    }
    void setGravity(Map& m) {
        vec2i blockbeneath = standingOn();
        // If block below is not solid
        //std::cout << "Index: "<< m.getTile(blockbeneath.y, blockbeneath.x).index << std::endl;
        if (!m.getTile(blockbeneath.y, blockbeneath.x).solid)
        {
            //std::cout << "not solid" << std::endl;
            velocity.y = fallVelocity;
        }
        else {
            //std::cout << "solid" << std::endl;
            velocity.y = 0;
        }
    }
    // Returns the tile the entity is standing on
    vec2i standingOn() {
        //Standing on tile of xth index and y+1th index
        return { static_cast<int>(std::floor(hitbox.position.x / gd::tilesize)), static_cast<int>(std::floor(hitbox.position.y / gd::tilesize + 1)) };
    }
    // Returns the tile to the left of the entity
    vec2i blockToLeft() {
        // God knows why -0.7
        // I'm god
        // -0.7 because the sprite has left empty padding
        return { static_cast<int>(std::ceil(hitbox.position.x / gd::tilesize -0.7)), static_cast<int>(std::floor(hitbox.position.y / gd::tilesize)) };
    }

    // Returns the tile to the right of the entity
    vec2i blockToRight() {
        // God knows why +0.8
        // I'm god
        // +0.8 because the sprite has right empty padding
        return { static_cast<int>(std::floor(hitbox.position.x / gd::tilesize + 0.8)), static_cast<int>(std::floor(hitbox.position.y / gd::tilesize)) };
    }

};

class Player : public Entity {
public:
    Player(int i, int x, int y, int w, int h, int s) : Element(i, x, y, w, h, s, TextureList<Player>::getTexture(i)) {
        health = 10;
        velocity = { 0,0 };
    }
    // Updates everything for the entity
    void update(Map& m)
    {
        horizontalMotion(m);
        setGravity(m);
        move({ velocity.x * timeUnit, velocity.y * timeUnit });
        hitbox = sprite.getGlobalBounds();
    }

    void horizontalMotion(Map &m) {
        velocity.x = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            vec2i leftBlock = blockToLeft();
            if (!m.getTile(leftBlock.y, leftBlock.x).solid)
            {
                velocity.x = -1;

            }
        }
            
        // If block below is not solid
        //std::cout << "Index: "<< m.getTile(blockbeneath.y, blockbeneath.x).index << std::endl;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            vec2i rightBlock = blockToRight();
            if (!m.getTile(rightBlock.y, rightBlock.x).solid)
            {
                velocity.x = 1;

            }
        }
    }
};

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