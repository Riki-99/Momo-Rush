#include "loader.h"

int spriteSize = 56;
sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
int desktop_width = desktop.size.x;
int desktop_height = desktop.size.y;

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


void loadBackgroundSprites(sf::RenderWindow& window) {
	for (int i = 0; i < backgroundSpriteCt; i++)
	{
		// Converting textures into sprites
		sf::FloatRect bounds = backgroundSprites[i].getLocalBounds();
		float scaleX = desktop_width / bounds.size.x;
		float scaleY = desktop_height / bounds.size.y;
		backgroundSprites[i].setScale({ scaleX, scaleY});
	}
}

void loadCharacter(){
}

void loadAllSprites(sf::RenderWindow& window)
{
	loadBackgroundSprites(window);
}
