#pragma once
#include <SFML/Graphics.hpp>
#include <random>
// Refers to the desktop
extern sf::VideoMode desktop;

struct GlobalData {
	static float tilesize;
	static const int horizontalTiles = 16;
	static const int verticalTiles = 10;
	// This is how many tiles to the right of the screen the position of player is to be fixed
	static const int playerScreenTileX = 7;
	
	// Returns a random number between low and high, inclusive
	static int random(int low, int high)
	{
			// Create a random device and seed the generator
			std::random_device rd;  // Non-deterministic seed
			std::mt19937 gen(rd()); // Mersenne Twister RNG

			std::uniform_int_distribution<> distr(low, high); // range: [low to high]
			return distr(gen);
	}
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