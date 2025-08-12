#include <SFML/Graphics.hpp>
#include <iostream>
#include "loader.h"
#include "global.h"

int main(void)
{
	// Obtaining dimensions of the desktop
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktop, "Momo Rush");
	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			// Event for when the close button is pressed
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			
			// Clearing the window before each draw, setting rgb(0,0,0) as background color
			window.clear(sf::Color(0, 0, 0));

			// Drawing code goes here
			loadAllTextures();
			Background b1(0);
			Background b2(1);
			Background b3(2);
			b1.draw(window);
			b2.draw(window);
			b3.draw(window);
			Player p(0, 0, 0, 1, 1, 56);
			p.draw(window);
			Map m1("./Assets/map1.txt");
			m1.draw(window);
			window.display();
		}

	}
	return 0;
}