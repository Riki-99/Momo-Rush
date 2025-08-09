#include <SFML/Graphics.hpp>
#include <iostream>
#include "loader.h"
#include "drawer.h"

int main(void)
{
	sf::RenderWindow window(sf::VideoMode({800,600}), "Title");
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