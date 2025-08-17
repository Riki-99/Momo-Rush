#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.h"
#include "loader.h"
#include "map.h"
#include "entity.h"
#include "player.h"
#include "game.h"

int main(void)
{
	// Obtaining dimensions of the desktop, defined in global.cpp
	sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Momo Rush");
	loadAllTextures();
	int counter = 0;
	Background b1(0);
	Background b2(1);
	Background b3(2);
	Map::generate(10000);
	Map m1("./Assets/newmap.txt");
	Player p(0, 0, 0, 56, 56);
	p.move({ static_cast<float>(tilesize * 12) , 0.f}, m1);
	game g(p);
	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			// Event for when the close button is pressed
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color(0, 0, 0));
		
		if (g.onGoing())
		{
			p.update(m1);
		}
		b1.draw(window);
		b2.draw(window);
		b3.draw(window);
		m1.draw(window, static_cast<int>(p.getHitBox().position.x));
		p.draw(window);
		window.display();
	}
	return 0;
}