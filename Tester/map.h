#pragma once
#include "global.h"
#include "loader.h"

class Tile : virtual public Element
{
protected:
    int frameCt;
    const float frameDuration = 0.1f;
    int currentFrameIdx;
    Clock clk;
    int width, height;
    vector <imageData> imgData;
public:
    bool consumed;
    // Index of the tile used.
    bool trap;
    int index;
    // Whether the tile is solid or not
    bool solid;
    Tile(int i, int x, int y, int w, int h, int c, int fct) : Element(i, x, y, w, h, TextureList<Tile>::getTexture(i)) {
        consumed = false;
        width = w;
        height = h;
        index = c; 
        if (c == 0 or c == 4)
        {
            solid = false;
            trap = false;
        }
        else if (c > 0 and c < 5)
        {
            solid = true;
            trap = false;
        }
        else {
            solid = false;
            trap = true;
        }
        frameCt = fct;
        currentFrameIdx = 0;
        if (frameCt>=2)
        {
            frameCt = fct;
            imgData.resize(fct);
            for (int i = 0; i < fct; i++)
            {
                imgData[i] = (imageData(i, 0, width, height));
            }
            clk.restart();
        }
    }
    Tile() : Element(0, 0, 0, 0, 0, tiletxtr) { index = 0; solid = bool(index); frameCt = 0; currentFrameIdx = 0;}
    void animate() {
        if (frameCt < 2) return;  // no frames to animate

        float timePassed = clk.getElapsedTime().asSeconds();
        if (timePassed >= frameDuration)
        {
            currentFrameIdx++;
            if (currentFrameIdx >= frameCt) {
                currentFrameIdx = 0;
            }
            imageData tmp = imgData[currentFrameIdx];
            intrect f = { { tmp.xCoords, tmp.yCoords }, { tmp.sizeX, tmp.sizeY } };
            sprite.setTextureRect(f);
            clk.restart();
        }
    }

    void draw(rw &window, float offset) {
        if (consumed == true) return;
        if (frameCt >= 2)
        {
            animate();
        }
        Element::draw(window, offset);
    }

};

class Map
{
    const int rows = 10;
    const int cols = 100;
    // a 2d vector for configuring all the tiles 
    std::vector < std::vector<Tile>> tiles;

public:
    // Setting the dimensions of rows and cols in runtime, initializing rows number of Tile vectors that contains yet another tile cols number of Tile vectors
    Map(str s);

    // safe bounds test
    bool inBounds(int row, int col) const;

    bool isSolid(int row, int col) const ;

    void  draw(rw& window, int playerXRealCoords);
    // Returns tile at map.tiles[i][j] (row, col) caller needs to make sure that the values will be inbound

    Tile& getTile(int i, int j);

    static string generate(int cols);
};