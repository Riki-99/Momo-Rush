#include "map.h"
#include "traps.h"

// Setting the dimensions of rows and cols in runtime, initializing rows number of Tile vectors that contains yet another tile cols number of Tile vectors
Map::Map(str s) : tiles(rows) {
    cout << "Check point a" << endl;
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
                tiles[i].push_back(Tile(0, 4, 0, 24, 24, 0, 1));
                break;
            case 1:
                tiles[i].push_back(Tile(0, 12, 0, 24, 24, 1, 1));
                break;
            case 2:
                tiles[i].push_back(Tile(0, 10, 0, 24, 24, 2, 1));
                break;
            case 3:
                tiles[i].push_back(Tile(0, 15, 0, 24, 24, 3, 1));
                break;
            case 4:
                tiles[i].push_back(Tile(0, 0, 11, 24, 24, 4, 1));
                break;
                // Upto 4, we've got tiles and after 4, we've got traps
                // 5 to 8 we've got obstacles
            case 5:
                tiles[i].push_back(bearTrap(32, 32, 4));
                break;
            case 6:
                tiles[i].push_back(fireTrap(32, 41, 14));
                break;
            case 7:
                tiles[i].push_back(pitTrap(32, 32, 1));
                break;
            case 8:
                tiles[i].push_back(spikeTrap(32, 41, 14));
                break;
            default:
                tiles[i].push_back(Tile(0, 4, 0, 24, 24, 0, 0));
            }
            // place in world coords
            tiles[i][tiles[i].size() - 1].setOnTile(j, i);
        }
    }
    cout << "Check point b" << endl;
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


// Returns tile at map.tiles[i][j] (row, col)
Tile& Map::getTile(int i, int j)
{
    if(inBounds(i,j))
        return tiles[i][j];
    return tiles[0][0];
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
                if (rand <= 60)
                {
                    rand = 0;
                }
                // 15% texture 1
                else if (rand <= 77)
                {
                    rand = 1;
                }
                // 15% texture 2
                else if (rand <= 94) {
                    rand = 2;
                }
                else if (rand <= 96)
                {
                    rand = 5;
                }
                else if (rand <= 98)
                {
                    rand = 6;
                }
                // Trap 7 needs to be down 
                else {
                    rand = 8;
                }
                file << rand;
            }
            else if (i == 8)
            {
                rand = gd::random(0, 100);
                if (rand <= 49)
                {
                    rand = 1;
                }
                else if (rand <= 98) {
                    rand = 2;
                }
                else {
                    // Pit fall in the lower layer
                    rand = 7;
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