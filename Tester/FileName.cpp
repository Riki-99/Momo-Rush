#include <SFML/Graphics.hpp>
#include <iostream>

int main(void)
{
	sf::RenderWindow window(sf::VideoMode({800,600}), "Title");
	sf::Texture txt("./Assets/oak-resources/background/background_layer_3.png");
	sf::Sprite sprt(txt);
	sprt.setScale({3,3});

	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			window.clear(sf::Color(0, 0, 0));
			window.draw(sprt);
			window.display();
		}

	}
	return 0;
}