#ifndef LOADER
#define LOADER

#include <SFML/Graphics.hpp>
#include <vector>

extern sf::Texture backgroundTextures[3];
extern sf::Sprite backgroundSprites[3];
extern int spriteCt;

void setBackgroundSprites(sf::RenderWindow& window);
void loadAllSprites(sf::RenderWindow& window);

#endif