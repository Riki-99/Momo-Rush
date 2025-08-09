#include "loader.h"
// There are three background nested
sf::Texture backgroundTextures[] = {
	sf::Texture("./Assets/oak-resources/background/background_layer_1.png"),
	sf::Texture("./Assets/oak-resources/background/background_layer_2.png"),
	sf::Texture("./Assets/oak-resources/background/background_layer_3.png")
};

sf::Sprite backgroundSprites[]
{
	sf::Sprite(backgroundTextures[0]),
	sf::Sprite(backgroundTextures[1]),
	sf::Sprite(backgroundTextures[2]),
};

int spriteCt = sizeof(backgroundSprites) / sizeof(backgroundSprites[0]);

void setBackgroundSprites() {
	for (int i = 0; i < spriteCt; i++)
	{

	}
}