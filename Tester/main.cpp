#include <SFML/Graphics.hpp>
#include <iostream>
#include "loader.h"
#include "global.h"

int main(void)
{
	// Obtaining dimensions of the desktop
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktop, "Momo Rush");
	loadAllTextures();
	int counter = 0;
	Background b1(0);
	Background b2(1);
	Background b3(2);
	Player p(0, 0, 0, 1, 1, 56);
	p.sprite.move({ static_cast<float>(gd::tilesize * 6) , 0.f});
	//Map m1("./Assets/map1.txt");
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
		b1.draw(window);
		b2.draw(window);
		b3.draw(window);
		Map m1("./Assets/map1.txt");
		m1.draw(window);
		p.draw(window);
		p.update(m1);
		window.display();
		counter++;
	}
	return 0;
}