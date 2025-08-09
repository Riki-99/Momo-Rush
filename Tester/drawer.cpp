#include "drawer.h"

void drawBackGroundSprites(sf::RenderWindow& window)
{
	for (int i = 0; i < spriteCt; i++)
	{
		// Drawing the sprites
		window.draw(backgroundSprites[i]);
	}
}

void drawAllSprites(sf::RenderWindow& window)
{
	drawBackGroundSprites(window);
}