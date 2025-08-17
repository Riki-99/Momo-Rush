#pragma once
#include <SFML/Graphics.hpp>
#include <random>
// Refers to the desktop

struct GlobalData {
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

inline float tilesize = 1080 / 10.f;
inline const int horizontalTiles = 16;
inline const int verticalTiles = 10;
// This is how many tiles to the right of the screen the position of player is to be fixed
inline const int playerScreenTileX = 7;
inline const sf::Vector2i desktop = { 1920, 1080 };

typedef sf::RenderWindow rw;
typedef sf::Sprite Sprt;
typedef sf::Texture Txt;
typedef std::string str;
typedef sf::Vector2f vec2f;
typedef sf::Vector2i vec2i;
typedef sf::FloatRect floatrect;
typedef sf::IntRect intrect;
typedef sf::Clock Clock;
typedef GlobalData gd;