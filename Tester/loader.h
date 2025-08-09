#ifndef LOADER
#define LOADER

#include <SFML/Graphics.hpp>
#include <vector>

class Resource{
public:
	std::string location;
	sf::Sprite sprite;
	Resource(std::string& l, sf::Vector2u& sc, sf::Sprite& sp) : location(l), scale(sc), sprite(sp) {};
};

#endif