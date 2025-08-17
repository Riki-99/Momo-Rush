#pragma once
#include "global.h"
#include "loader.h"

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
    Map(str s);

    // safe bounds test
    bool inBounds(int row, int col) const;

    bool isSolid(int row, int col) const ;

    void  draw(rw& window, int playerXRealCoords);
    // Returns tile at map.tiles[i][j] (row, col) caller needs to make sure that the values will be inbound

    Tile& getTile(int i, int j);

    static string generate(int cols);
};