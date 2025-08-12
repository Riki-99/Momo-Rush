#pragma once
#include <SFML/Graphics.hpp>
// Refers to the desktop
extern sf::VideoMode desktop;

struct GlobalData {
	static float tilesize;
	static const int horizontalTiles = 16;
	static const int verticalTiles = 10;
};
typedef sf::RenderWindow rw;
typedef sf::Sprite Sprt;
typedef sf::Texture Txt;
typedef std::string str;
typedef sf::Vector2f vec2f;
typedef sf::Vector2i vec2i;
typedef sf::FloatRect floatrect;
typedef sf::IntRect intrect;

typedef GlobalData gd;