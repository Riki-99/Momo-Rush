#include "loader.h"
#include <vector>

// Dimensions of each sprite in the player spritesheet
int playerSpriteSize = 56;
sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
int desktop_width = desktop.size.x;
int desktop_height = desktop.size.y;
// One tile to be 1/10th of the height of the desktop
float tileSize = (desktop_height / 10);

// The map
Map map;
Player player;

sf::Texture tileTexture("./Assets/oak-resources/oak_woods_tileset.png");
sf::Texture transprt("./Assets/oak-resources/oak_woods_tileset.png", false, sf::IntRect({ TileSprites::dim * 4, 0 }, { TileSprites::dim, TileSprites::dim }));
std::vector <TileFramework> tileSet = {
TileFramework(tileTexture, 4, 0, 1, 1, true),
TileFramework(tileTexture, 10, 0, 1, 1, false),
TileFramework(tileTexture, 12, 0, 1, 1, false),
TileFramework(tileTexture, 15, 0, 1, 1, false),
TileFramework(tileTexture, 0, 11, 1, 1, false)
};

// Textures are loaded
// There are three backgrounds nested
sf::Texture backgroundTextures[] = {
	sf::Texture("./Assets/oak-resources/background/background_layer_1.png"),
	sf::Texture("./Assets/oak-resources/background/background_layer_2.png"),
	sf::Texture("./Assets/oak-resources/background/background_layer_3.png")
};

// Creating sprites from backbround textures
sf::Sprite backgroundSprites[]{
	 sf::Sprite(backgroundTextures[0]),
	 sf::Sprite(backgroundTextures[1]),
	 sf::Sprite(backgroundTextures[2]),
};

// Number of background sprites
int backgroundSpriteCt = 3;

sf::Vector2f getScales(sf::Sprite & sprite)
{
	sf::FloatRect localBounds = sprite.getLocalBounds();
	return sf::Vector2f{desktop_width/localBounds.size.x, desktop_height/localBounds.size.y};
}


void loadBackgroundSprites(sf::RenderWindow& window) {
	for (int i = 0; i < backgroundSpriteCt; i++)
	{
		// Converting textures into sprites
		sf::FloatRect bounds = backgroundSprites[i].getLocalBounds();
		backgroundSprites[i].setScale(getScales(backgroundSprites[i]));
	}
}

sf::Texture playerTexture("./Assets/character-resources/png/blue/char_blue_1.png");
sf::Texture enemyTexture("./Assets/character-resources/png/red/char_red_1.png");

sf::Sprite playerSprite(playerTexture);
sf::Sprite enemySprite(enemyTexture);



void loadCharacters(){

	playerSprite.setTextureRect(sf::IntRect({0*playerSpriteSize, 0*playerSpriteSize}, {playerSpriteSize, playerSpriteSize}));
	enemySprite.setTextureRect(sf::IntRect({0*playerSpriteSize, 0*playerSpriteSize}, {playerSpriteSize, playerSpriteSize}));

	// Obtaining default size of the characters
	sf::FloatRect bounds = enemySprite.getLocalBounds();
	float height = bounds.size.x;
	float width = bounds.size.y;

	// Setting uniform scale
	enemySprite.setScale({ tileSize / width, tileSize / height });

	playerSprite.setScale({ tileSize / width, tileSize / height });
	float playerX = tileSize * 4, playerY = tileSize * 0;
	player = Player(10, {0,0}, playerSprite);

	float enemyX = tileSize * 4, enemyY = tileSize * 0;

    playerSprite.setPosition(player.sprite.getPosition());
    enemySprite.setPosition(sf::Vector2f(4 * playerSpriteSize, 4 * playerSpriteSize));
}


// Loading maps
sf::Texture mapTexture("./Assets/oak-resources/oak_woods_tileset.png");
sf::Sprite mapSprite(mapTexture);

void loadMap() {
	std::ifstream file("./Assets/map1.txt");
	map.load(file);
}

void loadAllSprites(sf::RenderWindow& window)
{
	loadBackgroundSprites(window);
	loadCharacters();
	loadMap();
}