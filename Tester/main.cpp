#include <SFML/Graphics.hpp>
#include <iostream>
#include "loader.h"
#include "drawer.h"

int main(void)
{
	// Obtaining dimensions of the desktop
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktop, "Momo Rush");
	loadAllSprites(window);
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
			drawAllSprites(window);
			window.display();
		}

	}
	return 0;
}