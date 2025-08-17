#include "map.h"

    // Setting the dimensions of rows and cols in runtime, initializing rows number of Tile vectors that contains yet another tile cols number of Tile vectors
    Map::Map(str s) : tiles(rows) {
        int tmp;
        std::ifstream file(s);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < 10000; j++)
            {
                if (!(file >> tmp)) tmp = 0; // safe fallback if file shorter than expected
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
                    break;
                default:
                    tiles[i].push_back(Tile(0, 4, 0, 1, 1, 24, 0));
                }
                // place in world coords
                tiles[i][tiles[i].size() - 1].setOnTile(j, i);
            }
        }
    }

    // safe bounds test
    bool Map::inBounds(int row, int col) const {
        if (row < 0 || row >= static_cast<int>(tiles.size())) return false;
        if (col < 0 || col >= static_cast<int>(tiles[row].size())) return false;
        return true;
    }

    bool Map::isSolid(int row, int col) const {
        if (!inBounds(row, col)) return false;
        return tiles[row][col].solid;
    }

    void  Map::draw(rw& window, int playerXRealCoords) {
        // how many tiles to draw to each side of the player
        const int viewRange = 16;
        const int playerScreenTileX = 7; // where on screen the player is fixed (in tiles)
        // camera offset in pixels: world, actual x of player - screen or displaying x of player
        float cameraOffsetPx = static_cast<float>(playerXRealCoords - playerScreenTileX * gd::tilesize);
        int playerXRealIndex = static_cast<int>(playerXRealCoords / gd::tilesize);

        for (int i = 0; i < static_cast<int>(tiles.size()); i++)
        {
            // Putting the player in center and drawing equally to the left and right side of the player
            int start = playerXRealIndex - viewRange;
            int end = playerXRealIndex + viewRange;
            if (start < 0) start = 0;
            if (end >= static_cast<int>(tiles[i].size())) end = static_cast<int>(tiles[i].size()) - 1;
            for (int j = start; j <= end; j++)
            {
                // draw each tile offset by camera
                tiles[i][j].draw(window, cameraOffsetPx);
            }
        }
    }


    // Returns tile at map.tiles[i][j] (row, col) caller needs to make sure that the values will be inbound
    Tile& Map::getTile(int i, int j)
    {
        return tiles[i][j];
    }

    string Map::generate(int cols)
    {
        string name = "./Assets/newmap.txt";
        ofstream file(name);
        int rand;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (i <= 6)
                {
                    file << 0;
                }
                else if (i == 7)
                {
                    rand = gd::random(0, 100);
                    // 70% texture 0
                    if (rand <= 70)
                    {
                        rand = 0;
                    }
                    // 15% texture 1
                    else if (rand <= 85)
                    {
                        rand = 1;
                    }
                    // 15% texture 2
                    else {
                        rand = 2;
                    }
                    file << rand;
                }
                else if (i == 8)
                {
                    rand = gd::random(0, 100);
                    if (rand <= 50)
                    {
                        rand = 1;
                    }
                    else {
                        rand = 2;
                    }
                    file << rand;
                }
                else if (i == 9)
                {
                    file << 3;
                }
                file << " ";
            }
            file << endl;
        }
        return name;
    }