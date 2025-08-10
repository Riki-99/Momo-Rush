#include "drawer.h"
#include <iostream>
void drawBackGroundSprites(sf::RenderWindow& window)
{
	for (int i = 0; i < backgroundSpriteCt; i++)
	{
		// Drawing the sprites
		window.draw(backgroundSprites[i]);
	}
}

void drawCharacters(sf::RenderWindow& window) {
	window.draw(enemySprite);
	window.draw(playerSprite);
}

void drawMap(sf::RenderWindow& window)
{
	map.display();
	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			// Drawing the sprites as per the value stored in the map indices.
			int currentIdx = map.indices[i][j];
			// Upadting the position of 
			tileSet[currentIdx].sprite.setPosition({ tileSize * j, tileSize * i});
			window.draw(tileSet[currentIdx].sprite);
		}
		std::cout << std::endl;
	}
}

void drawAllSprites(sf::RenderWindow& window)
{
	drawBackGroundSprites(window);
	drawMap(window);
	drawCharacters(window);
}
