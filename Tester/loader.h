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

// Dimensional information about each tile from the tile sourcce image
class TileSprites {
public:
	// Dimension
	static const int dim = 24;
	static const int spriteHorizonatalTiles = 21;
	static const int spriteVerticalTiles = 15;
};

// Blue prints for the tiles used
class TileFramework{
public: 
		sf::Sprite sprite;
		// Coordinates of where to crop from the texture
		sf::Vector2i spriteCoords;
		// Size of how much to crop from the texture
		sf::Vector2i playerSpriteSize;
		bool solid;
		void crop()
		{
			sprite.setTextureRect(sf::IntRect(spriteCoords, playerSpriteSize));
		}
		TileFramework(sf::Texture& t, int X, int Y, int w, int h, bool s) : spriteCoords{ X * TileSprites::dim, Y * TileSprites::dim }, playerSpriteSize{ w * TileSprites::dim ,h * TileSprites::dim }, sprite(t), solid(s)
		{
			crop();
			sprite.setScale({ tileSize / TileSprites::dim, tileSize / TileSprites::dim });
		}
		// Initializing with a transparent sprite for default constructor
		TileFramework() : sprite(transprt) {}
};

extern std::vector <TileFramework> tileSet;


class Tile {
public:
	// Details about each individual tile
	int xIdx, yIdx;
	// Coordinates
	sf::FloatRect hitbox;
	TileFramework blueprint;
	Tile(){}
	Tile(int x, int y, sf::FloatRect r, TileFramework t): xIdx(x), yIdx(y), hitbox(r), blueprint(t){}
};

class Map {
public:
	// Sprite containing all details
	Tile tile[10][16];
	const int rows = 10;
	const int cols = 16;
	void load(std::ifstream& ifstr)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				// The outer apperance of each tile is obtained from a text file
				int tileskin;
				ifstr >> tileskin;
				tile[i][j] = Tile(i, j, sf::FloatRect({i*tileSize, j*tileSize},{tileSize, tileSize}), tileSet[tileskin]);
			}
		}
	}

	Map(){}

	void display(){
		/*for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << tile[i][j]. << " ";
			}
			std::cout << std::endl;
		}*/
	}
};

class Entity {
public:
	int hearts;
	sf::Sprite sprite;
	sf::Vector2f velocity;
	Entity(int h, sf::Vector2f vel, sf::Sprite s)  : hearts(h), velocity(vel), sprite(s){}
	// Placeholder transparent sprite
	Entity(): sprite(transprt){}
};

class Player : public Entity {
public:
	Player(int h, sf::Vector2f v, sf::Sprite& s) : Entity(h, v, s){}
	Player(): Entity(){}
};

extern sf::Texture mapTexture;
extern sf::Sprite mapSprite;
extern Map map;

#endif