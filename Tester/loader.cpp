#include "loader.h"
// There are three backgrounds nested
// Textures are loaded
sf::Texture backgroundTextures[] = {
	sf::Texture("./Assets/oak-resources/background/background_layer_1.png"),
	sf::Texture("./Assets/oak-resources/background/background_layer_2.png"),
	sf::Texture("./Assets/oak-resources/background/background_layer_3.png")
};

sf::Sprite backgroundSprites[]{
	 sf::Sprite(backgroundTextures[0]),
	 sf::Sprite(backgroundTextures[1]),
	 sf::Sprite(backgroundTextures[2]),
};

int spriteCt = 3;

void setBackgroundSprites(sf::RenderWindow& window) {
	for (int i = 0; i < spriteCt; i++)
	{
		// Converting textures into sprites
		backgroundSprites[i].setScale({ 3,3 });
	}
}

void loadAllSprites(sf::RenderWindow& window)
{
	setBackgroundSprites(window);
}
