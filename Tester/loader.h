#ifndef LOADER
#define LOADER

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

extern int desktop_width;
extern int desktop_height;
extern float tileSize;


extern sf::Texture backgroundTextures[3];
extern sf::Sprite backgroundSprites[3];
extern int backgroundSpriteCt;

extern sf::Sprite playerSprite;
extern sf::Sprite enemySprite;
extern sf::Texture transprt;

void loadBackgroundSprites(sf::RenderWindow& window);
void loadAllSprites(sf::RenderWindow& window);

class TileSprites {
public:
	// Dimension
	static const int dim = 24;
	static const int spriteHorizonatalTiles = 21;
	static const int spriteVerticalTiles = 15;
};
class Tile {
public: 
		sf::Sprite sprite;
		// Coordinates of where to crop from the texture
		sf::Vector2i spriteCoords;
		// Size of how much to crop from the texture
		sf::Vector2i spriteSize;
		bool solid;
		void crop()
		{
			sprite.setTextureRect(sf::IntRect(spriteCoords, spriteSize));
		}
		Tile(sf::Texture& t, int X, int Y, int w, int h, bool s) : spriteCoords{ X * TileSprites::dim, Y * TileSprites::dim }, spriteSize{ w * TileSprites::dim ,h * TileSprites::dim }, sprite(t), solid(s)
		{
			crop();
			sprite.setScale({ tileSize / TileSprites::dim, tileSize / TileSprites::dim });
		}
		// Initializing with a transparent sprite for default constructor
		Tile() : sprite(transprt) {}
};


class Map {
public:
	// Sprite containing all tiles
	int indices[10][16];
	const int rows = 10;
	const int cols = 16;
	void load(std::ifstream& ifstr)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				ifstr >> indices[i][j];
			}
		}
	}

	Map(){}

	void display(){
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << indices[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

extern sf::Texture mapTexture;
extern sf::Sprite mapSprite;
extern Map map;
extern std::vector <Tile> tileSet;

#endif